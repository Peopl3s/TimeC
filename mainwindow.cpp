#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "ProgressCircle.h"
#include "timec.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowIcon(QIcon("Live-Mathletics-Timer-Picture-2014.png"));
    setWindowTitle("TimeC");
    TimeC *t=new TimeC;
    setCentralWidget(t);

}

MainWindow::~MainWindow()
{
    delete ui;
}
