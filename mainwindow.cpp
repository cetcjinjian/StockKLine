#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "klinegrid.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pgrid = new KLineGrid(this);
    pgrid->setObjectName(tr("kline"));
    pgrid->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(pgrid);
    resize(1200,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
