#include "MyImageIOPlugin.h"

#include <QIODevice>
#include <QImage>
#include <iostream>

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
    std::cout << "Checking for zmos" << std::endl;
    if(format.startsWith("zmos")) {
        std::cout << "YES!" << std::endl;
        return QImageIOPlugin::CanRead;
    }
    else {
        std::cout << format.at(0) << std::endl;
        return 0;
    }
}

QStringList MyImageIOPlugin::keys() const {
    return QStringList("zmos");
}

QImageIOHandler* MyImageIOPlugin::create(QIODevice *device, const QByteArray &format) const {
    std::cout << "Creating!" << std::endl;
    return new MyImageIOHandler;
}

bool MyImageIOHandler::canRead () const {
    return true;
}

bool MyImageIOHandler::read ( QImage * image ) {
    std::cout << "LOADING zmos IMAGE" << std::endl;
    QByteArray data = device()->readAll();
    std::cout << "Bytes read: " << data.count() << std::endl;
    QImage myImg("/home/sebastian/bla/bla.png");
    *image = myImg;
    return true;
}
