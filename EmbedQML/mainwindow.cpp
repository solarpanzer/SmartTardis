#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QGraphicsObject>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QImageReader>
#include <QDeclarativeImageProvider>
#include <QPluginLoader>

#include <iostream>

class DiskImageProvider : public QDeclarativeImageProvider
{
public:
    DiskImageProvider()
        : QDeclarativeImageProvider(QDeclarativeImageProvider::Image)
    {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)
    {
        std::cout << "Delivering "<< id.toStdString() << "." << std::endl;
        QImage img;
        img.load(QString("/home/sebastian/bla/") + id);

        int width= img.width();
        int height = img.height();

        if(size)
            *size = QSize(width, height);

        if(requestedSize.width() > 0 && requestedSize.height() > 0)
            img=img.scaled(requestedSize);

        return img;
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->declarativeView->engine()->addImageProvider("bla", new DiskImageProvider);
    ui->declarativeView->setSource(QUrl::fromLocalFile("../SmartTardis/SmartTardis.qml"));

    QGraphicsObject* rootGraphicsObject = ui->declarativeView->rootObject();
    QObject* rootObject = dynamic_cast<QObject*>(rootGraphicsObject);
    QObject::connect(rootObject, SIGNAL(itemClicked(QString, QString)), this, SLOT(itemClicked(QString, QString)));
    QObject::connect(this, SIGNAL(newData(QVariant, QVariant)), rootObject, SLOT(setItems(QVariant, QVariant)));

//    QStringList names;
//    QStringList urls;

//    for(int i=0; i<20; i++)
//    {
//        names.append(QString("Bild ") + ('a' + i));
//        urls.append("tardis.jpg");
//    }

//    emit(newData(QVariant::fromValue(names), QVariant::fromValue(urls)));

    QObject::connect(ui->actionLoad_images_from_dir, SIGNAL(triggered()), this, SLOT(loadImageDir()));
    loadImageDir("/home/sebastian/zmos");

    std::cout << " asdf " << QPluginLoader::staticInstances().count();
    foreach (QObject *plugin, QPluginLoader::staticInstances())
        std::cout << plugin->metaObject()->className();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::itemClicked(const QString &name, const QString &url)
{
    std::cerr << "item selected: " << name.toStdString() << ", " << url.toStdString() << std::endl;
    ui->textBrowser->setText(name + "\n" + url);
}

void MainWindow::loadImageDir()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select Image Dir"));
    loadImageDir(dirName);
}

void MainWindow::loadImageDir(QString dirName)
{
    QDir myDir(dirName);

    QStringList filter;
    filter.append("*.jpg");
    filter.append("*.png");
    filter.append("*.bmp");
    filter.append("*.zmos");
    QFileInfoList imageList = myDir.entryInfoList(filter);

    QStringList names;
    QStringList urls;
    for(int i=0; i<imageList.count(); i++)
    {
        const QFileInfo& info = imageList[i];
        names.append(info.fileName());
        urls.append(info.filePath());
        //urls.append(QString("image://bla/" + info.fileName()));
    }

    emit(newData(QVariant::fromValue(names), QVariant::fromValue(urls)));
}
