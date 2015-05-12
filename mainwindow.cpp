#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    docket = new DockWidgetImages();
    this->addDockWidget(Qt::RightDockWidgetArea,docket);
    docket->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_test1_clicked()
{
    docket->toggleShowHide();
}
