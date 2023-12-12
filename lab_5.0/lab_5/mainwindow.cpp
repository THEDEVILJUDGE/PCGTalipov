#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //l->addWidget(p,0,0,12,1);
    pbCentral = new QPushButton;
    pbCentral->setText("Central point Algorythm");
    pbCirus = new QPushButton;
    pbCirus->setText("Cirus-Beck Algorythm");
    l->addWidget(pbCentral,0,1,1,1);
    l->addWidget(pbCirus,1,1,1,1);
    ui->centralwidget->setLayout(l);
    connect(pbCentral, SIGNAL(clicked()), this, SLOT(showCentral()));
    connect(pbCirus, SIGNAL(clicked()), this, SLOT(showCirus()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

