#ifndef MYIMAGEIOPLUGIN_H
#define MYIMAGEIOPLUGIN_H

#define QT_STATICPLUGIN

#include <QImageIOPlugin>

class MyImageIOPlugin : public QImageIOPlugin {
    Q_OBJECT;

    virtual Capabilities capabilities ( QIODevice * device, const QByteArray & format ) const;
    virtual QImageIOHandler* create ( QIODevice * device, const QByteArray & format = QByteArray() ) const;
    virtual QStringList	keys () const;
};

#endif // MYIMAGEIOPLUGIN_H
