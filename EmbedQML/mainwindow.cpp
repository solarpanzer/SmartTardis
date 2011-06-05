#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QGraphicsObject>
#include <QDeclarativeContext>
#include <QStandardItemModel>
#include <QFileDialog>

#include <iostream>

#include "roleitemmodel.h"

struct ModelRoles {
    enum ItemRoles {
        NameRole = Qt::UserRole + 1,
        UrlRole,
    };
};

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

    //    QHash<int, QByteArray> roleNames;
    //    roleNames[ModelRoles::NameRole] = "name";
    //    roleNames[ModelRoles::UrlRole] =  "url";
    //    RoleItemModel* model = new RoleItemModel(roleNames);
//    //QStandardItemModel model(4, 4);
////    QStandardItemModel* model = new QStandardItemModel(5,2);
//    for (int row = 0; row < 20; ++row) {
//        QStandardItem* it = new QStandardItem();
//        it->setData(QString("Item ") + ('a'+row), ModelRoles::NameRole);
//        it->setData("tardis.jpg", ModelRoles::UrlRole);
//        model->appendRow(it);
//    }
////    model->setHorizontalHeaderItem(0, new QStandardItem(QString("name")));
////    model->setHorizontalHeaderItem(1, new QStandardItem(QString("url")));

//    QDeclarativeContext* ctx = ui->declarativeView->rootContext();
//    ctx->setContextProperty("itemList", model);

////    QObject* itemListObject = rootObject->findChild<QObject*>("itemList");
////    QAbstractItemModel* itemList = dynamic_cast<QAbstractTableModel*>(itemListObject);
////    if(itemList == NULL)
////        std::cerr << "itemList == NULL" << std::endl;
//    ui->tableView->setModel(model);
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
