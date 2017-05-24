#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "klinegrid.h"
#include <QTextCodec>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

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
