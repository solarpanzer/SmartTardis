#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QGraphicsObject>
#include <QDeclarativeContext>
#include <QStandardItemModel>
#include <QFileDialog>

#include <iostream>

#include "roleitemmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->declarativeView->setSource(QUrl::fromLocalFile("../SmartTardis/SmartTardis.qml"));

    QGraphicsObject* rootGraphicsObject = ui->declarativeView->rootObject();
    QObject* rootObject = dynamic_cast<QObject*>(rootGraphicsObject);
    QObject::connect(rootObject, SIGNAL(itemClicked(QString, QString)), this, SLOT(itemClicked(QString, QString)));

    QStringList names;
    QStringList urls;

    for(int i=0; i<20; i++)
    {
        names.append(QString("Bild ") + ('a' + i));
        urls.append("tardis.jpg");
    }

    QObject::connect(this, SIGNAL(newData(QVariant, QVariant)), rootObject, SLOT(setItems(QVariant, QVariant)));
    emit(newData(QVariant::fromValue(names), QVariant::fromValue(urls)));

    QObject::connect(ui->actionLoad_images_from_dir, SIGNAL(triggered()), this, SLOT(loadImageDir()));
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
    QDir myDir(dirName);

    QStringList filter;
    filter.append("*.jpg");
    filter.append("*.png");
    QFileInfoList imageList = myDir.entryInfoList(filter);

    QStringList names;
    QStringList urls;
    for(int i=0; i<imageList.count(); i++)
    {
        const QFileInfo& info = imageList[i];
        names.append(info.fileName());
        urls.append(info.filePath());
    }

    emit(newData(QVariant::fromValue(names), QVariant::fromValue(urls)));
}
