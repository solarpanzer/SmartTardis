#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QGraphicsObject>
#include <QDeclarativeContext>
#include <QStandardItemModel>

#include <iostream>

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

    //QStandardItemModel model(4, 4);
//    QStandardItemModel* model = new QStandardItemModel(5,2);
//    for (int row = 0; row < 4; ++row) {
//        for (int column = 0; column < 2; ++column) {
//            QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
//            model->setItem(row, column, item);
//        }
//    }
//    model->setHorizontalHeaderItem(0, new QStandardItem(QString("name")));
//    model->setHorizontalHeaderItem(1, new QStandardItem(QString("url")));

//    QDeclarativeContext* ctx = ui->declarativeView->rootContext();
//    ctx->setContextProperty("itemList", model);

//    QObject* itemListObject = rootObject->findChild<QObject*>("itemList");
//    QAbstractItemModel* itemList = dynamic_cast<QAbstractTableModel*>(itemListObject);
//    if(itemList == NULL)
//        std::cerr << "itemList == NULL" << std::endl;
    //ui->tableView->setModel(itemList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::itemClicked(const QString &name, const QString &url)
{
    std::cerr << "item selected: " << name.toStdString() << ", " << url.toStdString() << std::endl;
}
