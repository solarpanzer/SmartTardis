#define QT_STATICPLUGIN

#include <QImageIOPlugin>
#include <QIODevice>
#include <QImage>
#include <iostream>

class MyImageIOPlugin : public QImageIOPlugin {
    virtual Capabilities capabilities ( QIODevice * device, const QByteArray & format ) const;
    virtual QImageIOHandler* create ( QIODevice * device, const QByteArray & format = QByteArray() ) const;
    virtual QStringList	keys () const;
};

//Q_EXPORT_PLUGIN(MyImageIOPlugin)
Q_EXPORT_PLUGIN2(pnp_myimageioplugin, MyImageIOPlugin);
Q_IMPORT_PLUGIN(pnp_myimageioplugin);

class MyImageIOHandler : public QImageIOHandler {
public:
    MyImageIOHandler() { std::cout << "MyImageIOHandler created." << std::endl; }
    bool canRead () const;
    virtual bool read ( QImage * image );
};

QImageIOPlugin::Capabilities MyImageIOPlugin::capabilities(QIODevice *device, const QByteArray &format) const {
    if(format.startsWith("zmos1")) {
        return QImageIOPlugin::CanRead;
    }
    else {
        return 0;
    }
}

QStringList MyImageIOPlugin::keys() const {
    return QStringList("zmos1");
}

QImageIOHandler* MyImageIOPlugin::create(QIODevice *device, const QByteArray &format) const {
    return new MyImageIOHandler;
}

union ZiehmPixelFormat
{
  // For pixel-wise access
  struct
  {
    unsigned int pixel0 : 10;
    unsigned int pixel1 : 10;
    unsigned int pixel2 : 10;
    unsigned int _spare :  2;
  };

  // For DWord-wise access
  unsigned int dword;
};

bool MyImageIOHandler::canRead () const {
    return true;
}

bool MyImageIOHandler::read ( QImage * image ) {
    QByteArray data = device()->readAll();

    QImage myImg(256, 256, QImage::Format_RGB32);
    uchar* out = myImg.bits();
    ZiehmPixelFormat* in = (ZiehmPixelFormat*)(data.data() + 4096);

    int width = 256;
    int height = 256;

    for(int y=0; y<height; y++)
    {
        for(int x3=0; x3<width/3; x3++)
        {
            out[3] = out[7] = out[11] = 1;
            out[0] = out[1] = out[2] = in->pixel0 / 4; // 1024 -> 256 gray levels
            out[4] = out[5] = out[6] = in->pixel1 / 4;
            out[8] = out[9] = out[10] = in->pixel2 / 4;
            in++;
            out += 12;
        }
        int x = width/3*3;
        if(x<width)
        {
            // handle the remainder
            out[0] = out[1] = out[2] = in->pixel0 / 4;
            out[4] = 1;
            out += 4;
            if(x+1<width)
            {
                out[0] = out[1] = out[2] = in->pixel1 / 4;
                out[4] = 1;
                out += 4;
            }
            in++;
        }
    }

    *image = myImg;
    return true;
}
