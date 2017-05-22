#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pgrid = new AutoGrid(this);
    pgrid->setObjectName(tr("kline"));
    setCentralWidget(pgrid);
    resize(1200,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
