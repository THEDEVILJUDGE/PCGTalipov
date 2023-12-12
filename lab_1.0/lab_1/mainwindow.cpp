#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "module.h"
#include <QGridLayout>
#include <QPalette>
#include <QColorDialog>
#include <QObject>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QObject::connect(pbColor, SIGNAL(clicked()), this, SLOT(on_pbColor_clicked()));
    QObject::connect(m1, SIGNAL(changed()), this, SLOT(changeColor1()));
    QObject::connect(m2, SIGNAL(changed()), this, SLOT(changeColor2()));
    QObject::connect(m3, SIGNAL(changed()), this, SLOT(changeColor3()));
    QObject::connect(m1, SIGNAL(sliderMoved()), this, SLOT(changeColor1()));
    QObject::connect(m2, SIGNAL(sliderMoved()), this, SLOT(changeColor2()));
    QObject::connect(m3, SIGNAL(sliderMoved()), this, SLOT(changeColor3()));
    QPalette p = QPalette();
    p.setBrush(QPalette::Background, Qt::black);
    wColor->setAutoFillBackground(true);
    wColor->setPalette(p);
    ui->setupUi(this);
    QGridLayout* l = new QGridLayout;
    QLabel* lYourColor = new QLabel;
    lYourColor->setAlignment(Qt::AlignCenter);
    lYourColor->setText("Your color:");
    pbColor->setText("Choose color");
    lYourColor->setGeometry(0,0,2,2);
    m1->setType(type::RGB);
    m2->setType(type::CMYK);
    m3->setType(type::HLS);
    l->addWidget(lYourColor, 0, 1, 1, 2);
    l->addWidget(wColor, 1, 1, 2, 2);
    l->addWidget(pbColor, 1, 4, 2, 1);
    l->addWidget(m1, 3, 0, 4, 2);
    l->addWidget(m2, 3, 2, 4, 2);
    l->addWidget(m3, 3, 4, 4, 2);
    ui->centralwidget->setLayout(l);
    //resize(minimumSize());
}

void MainWindow::on_pbColor_clicked(){
    color = QColorDialog::getColor();
    setColors();
    setwColor();
}

void MainWindow::changeColor1(){
    m2->setRecalc();
    m3->setRecalc();
    m2->setSliderRecalc();
    m3->setSliderRecalc();
    color = m1->getColor();
    m2->setColor(color);
    m3->setColor(color);
    setwColor();
}

void MainWindow::changeColor2(){
    m1->setRecalc();
    m3->setRecalc();
    m1->setSliderRecalc();
    m3->setSliderRecalc();
    color = m2->getColor();
    m1->setColor(color);
    m3->setColor(color);
    setwColor();
}

void MainWindow::changeColor3(){
    m2->setRecalc();
    m1->setRecalc();
    m2->setSliderRecalc();
    m1->setSliderRecalc();
    color = m3->getColor();
    m2->setColor(color);
    m1->setColor(color);
    setwColor();
}

void MainWindow::setColors(){
    m1->setColor(color);
    m2->setColor(color);
    m3->setColor(color);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionRGB_LAB_CMYK_triggered()
{
    m1->setType(RGB);
    m2->setType(LAB);
    m3->setType(CMYK);
}

void MainWindow::on_actionCMYK_RGB_HSV_triggered()
{
    m1->setType(CMYK);
    m2->setType(RGB);
    m3->setType(HSV);
}

void MainWindow::setwColor(){
    QPalette p = QPalette();
    p.setBrush(QPalette::Background, color);
    wColor->setAutoFillBackground(true);
    wColor->setPalette(p);
}

void MainWindow::on_actionRGB_XYZ_CMYK_triggered()
{
    m1->setType(RGB);
    m2->setType(XYZ);
    m3->setType(CMYK);
}

void MainWindow::on_actionRGB_CMYK_HLS_triggered()
{
    m1->setType(RGB);
    m2->setType(CMYK);
    m3->setType(HLS);
}

void MainWindow::on_actionRGB_XYZ_HSV_triggered()
{
    m1->setType(RGB);
    m2->setType(XYZ);
    m3->setType(HSV);
}

void MainWindow::on_actionCMYK_LAB_XYZ_triggered()
{
    m1->setType(CMYK);
    m2->setType(LAB);
    m3->setType(XYZ);
}

void MainWindow::on_actionRGB_XYZ_LAB_triggered()
{
    m1->setType(RGB);
    m2->setType(XYZ);
    m3->setType(LAB);
}

void MainWindow::on_actionHSV_XYZ_LAB_triggered()
{
    m1->setType(HSV);
    m2->setType(XYZ);
    m3->setType(LAB);
}

void MainWindow::on_actionRGB_CMYK_HSV_triggered()
{
    m1->setType(RGB);
    m2->setType(CMYK);
    m3->setType(HSV);
}

void MainWindow::on_action_RGB_HSV_LAB_triggered()
{
    m1->setType(RGB);
    m2->setType(HSV);
    m3->setType(LAB);
}

void MainWindow::on_actionCMYK_LAB_RGB_triggered()
{
    m1->setType(CMYK);
    m2->setType(LAB);
    m3->setType(RGB);
}

void MainWindow::on_actionCMYK_HLS_XYZ_triggered()
{
    m1->setType(CMYK);
    m2->setType(HLS);
    m3->setType(XYZ);
}

void MainWindow::on_actionCMYK_LAB_HSV_triggered()
{
    m1->setType(CMYK);
    m2->setType(LAB);
    m3->setType(HSV);
}

void MainWindow::on_actionXYZ_LAB_HLS_triggered()
{
    m1->setType(XYZ);
    m2->setType(LAB);
    m3->setType(HLS);
}

void MainWindow::on_actionRGB_HLS_LAB_triggered()
{
    m1->setType(RGB);
    m2->setType(HLS);
    m3->setType(LAB);
}

void MainWindow::on_actionCMYK_RGB_HLS_triggered()
{
    m1->setType(CMYK);
    m2->setType(RGB);
    m3->setType(HLS);
}

void MainWindow::on_actionRGB_XYZ_HLS_triggered()
{
    m1->setType(RGB);
    m2->setType(XYZ);
    m3->setType(HLS);
}

void MainWindow::on_actionCMYK_XYZ_RGB_triggered()
{
    m1->setType(CMYK);
    m2->setType(XYZ);
    m3->setType(RGB);
}
