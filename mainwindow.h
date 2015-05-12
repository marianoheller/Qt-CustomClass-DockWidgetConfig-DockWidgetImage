#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dockwidgetimages.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_test1_clicked();

private:
    Ui::MainWindow *ui;
    DockWidgetImages *docket;
};

#endif // MAINWINDOW_H
