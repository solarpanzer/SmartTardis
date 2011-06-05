#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void newData(QVariant names, QVariant urls);

private:
    Ui::MainWindow *ui;

private slots:
    void itemClicked(const QString& name, const QString& url);
    void loadImageDir();

};

#endif // MAINWINDOW_H
