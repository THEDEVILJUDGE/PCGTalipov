#include "module.h"
#include <QGridLayout>
#include <QString>
#include <QDoubleValidator>
#include <QMessageBox>
#include <iostream>
#include <cmath>

Module::Module():QWidget()
{
    QObject::connect(le1, SIGNAL(textEdited(QString)), this, SLOT(le1Changed()));
    QObject::connect(le2, SIGNAL(textEdited(QString)), this, SLOT(le2Changed()));
    QObject::connect(le3, SIGNAL(textEdited(QString)), this, SLOT(le3Changed()));
    QObject::connect(le4, SIGNAL(textEdited(QString)), this, SLOT(le4Changed()));
    QObject::connect(s1, SIGNAL(valueChanged(int)), this, SLOT(s1Moved()));
    QObject::connect(s2, SIGNAL(valueChanged(int)), this, SLOT(s2Moved()));
    QObject::connect(s3, SIGNAL(valueChanged(int)), this, SLOT(s3Moved()));
    QObject::connect(s4, SIGNAL(valueChanged(int)), this, SLOT(s4Moved()));
    QGridLayout *l = new QGridLayout;
    lsystem->setAlignment(Qt::AlignCenter);
    l->addWidget(lsystem, 0, 1, 1, 1);
    l->addWidget(l1, 1, 0, 1, 1);
    l->addWidget(l2, 4, 0, 1, 1);
    l->addWidget(l3, 7, 0, 1, 1);
    l->addWidget(l4, 10, 0, 1, 1);
    l->addWidget(le1, 1, 1, 1, 2);
    l->addWidget(le2, 4, 1, 1, 2);
    l->addWidget(le3, 7, 1, 1, 2);
    l->addWidget(le4, 10, 1, 1, 2);
    l->addWidget(s1, 2, 0, 2, 3);
    l->addWidget(s2, 5, 0, 2, 3);
    l->addWidget(s3, 8, 0, 2, 3);
    l->addWidget(s4, 11, 0, 2, 3);
    this->setLayout(l);
}

void Module::s1Moved(){
    le1->setText(QString::number(s1->value()));
    if(sliderRecalc){
    le1Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

void Module::s2Moved(){
    le2->setText(QString::number(s2->value()));
    if(sliderRecalc){
    le2Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

void Module::s3Moved(){
    le3->setText(QString::number(s3->value()));
    if(sliderRecalc){
    le3Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

void Module::s4Moved(){
    le4->setText(QString::number(s4->value()));
    if(sliderRecalc){
    le4Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

void Module::leChanged(QLineEdit* le, int min, int max, bool needRecalc){
    //if(recalc){
    if(le->text().toDouble() > max){
        outOfRangeError(75);
        le->setText(QString::number(max));
    }
    if(le->text().toDouble() < min){
        outOfRangeError(79);
        le->setText(QString::number(min));
    }
    switch(type){
    case RGB:
        color.setRgb(le1->text().toDouble(), le2->text().toDouble(), le3->text().toDouble());
        break;
    case CMYK:
        color.setCmyk(le1->text().toDouble(), le2->text().toDouble(), le3->text().toDouble(), le4->text().toDouble());
        break;
    case LAB:
        color = colorFromLAB(le1->text().toDouble(), le2->text().toDouble(), le3->text().toDouble());
        break;
    case HSV:
        color.setHsv(le1->text().toDouble(), le2->text().toDouble(), le3->text().toDouble());
        break;
    case HLS:
        color.setHsl(le1->text().toDouble(), le3->text().toDouble(), le2->text().toDouble());
        break;
    case XYZ:
        color = colorFromXYZ(le1->text().toDouble(), le2->text().toDouble(), le3->text().toDouble());
        break;
    }
    if(!needRecalc){
        setSliders();
        emit changed();
    }
    //}
    recalc = true;
}

void Module::le1Changed(bool a){
    switch(type){
        case RGB:
        leChanged(le1, 0, 255, a);
        break;
    case CMYK:
        leChanged(le1, 0, 255, a);
        break;
    case LAB:
        leChanged(le1, 0, 100, a);
        break;
    case HSV:
        leChanged(le1, 0, 360, a);
        break;
    case HLS:
        leChanged(le1, 0, 255, a);
        break;
    case XYZ:
        leChanged(le1, 0, 100, a);
        break;
    }
}

void Module::le2Changed(bool a){
    switch(type){
        case RGB:
        leChanged(le2, 0, 255, a);
        break;
    case CMYK:
        leChanged(le2, 0, 255, a);
        break;
    case LAB:
        leChanged(le2, -128, 127, a);
        break;
    case HSV:
        leChanged(le2, 0, 255, a);
        break;
    case HLS:
        leChanged(le2, 0, 255, a);
        break;
    case XYZ:
        leChanged(le2, 0, 100, a);
        break;
    }
}

void Module::le3Changed(bool a){
    switch(type){
        case RGB:
        leChanged(le3, 0, 255, a);
        break;
    case CMYK:
        leChanged(le3, 0, 255, a);
        break;
    case LAB:
        leChanged(le3, -128, 127, a);
        break;
    case HSV:
        leChanged(le3, 0, 255, a);
        break;
    case HLS:
        leChanged(le3, 0, 255, a);
        break;
    case XYZ:
        leChanged(le3, 0, 100, a);
        break;
    }
}

void Module::le4Changed(bool a){
    leChanged(le4, 0, 255, a);
}

void Module::outOfRangeError(int s){
    QMessageBox::information(NULL,QObject::tr("Warning"),tr("Value out of range! " ));
    std::cout<<s;
}

void Module::setSliders(){
    setSliderRecalc();
    s1->setValue(le1->text().toInt());
    setSliderRecalc();
    s2->setValue(le2->text().toInt());
    setSliderRecalc();
    s3->setValue(le3->text().toInt());
    setSliderRecalc();
    s4->setValue(le4->text().toInt());
}

void Module::setType(enum::type t){
    type = t;
    QDoubleValidator* v1 = new QDoubleValidator();
    QDoubleValidator* v2 = new QDoubleValidator();
    QDoubleValidator* v3 = new QDoubleValidator();
    QDoubleValidator* v4 = new QDoubleValidator();
    switch (t)
    {
    case type::RGB:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("RGB");
        l1->setText("R");
        l2->setText("G");
        l3->setText("B");
        v1->setRange(0.0,255.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 255);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::CMYK:
        l4->show();
        le4->show();
        s4->show();
        lsystem->setText("CMYK");
        l1->setText("C");
        l2->setText("M");
        l3->setText("Y");
        l4->setText("K");
        v1->setRange(0.0,255.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 255);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        v4->setRange(0.0,255.0, 2);
        v4->setNotation(QDoubleValidator::StandardNotation);
        s4->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        le4->setValidator(v4);
        break;
    case type::LAB:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("LAB");
        l1->setText("L");
        l2->setText("a");
        l3->setText("b");
        v1->setRange(0.0,100.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 100);
        v2->setRange(-128.0,127.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(-128, 127);
        v3->setRange(-128.0,127.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(-128, 127);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::HSV:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("HSV");
        l1->setText("H");
        l2->setText("S");
        l3->setText("V");
        v1->setRange(0.0,360.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 359);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::HLS:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("HLS");
        l1->setText("H");
        l2->setText("L");
        l3->setText("S");
        v1->setRange(0.0,255.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 255);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::XYZ:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("XYZ");
        l1->setText("X");
        l2->setText("Y");
        l3->setText("Z");
        v1->setRange(0.0,100.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 100);
        v2->setRange(0.0,100.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 100);
        v3->setRange(0.0,100.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 100);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    }
    setColor(color);
}

void Module::setColor(QColor col){
    color = col;
    switch(type){
    case type::RGB:
        setRGB();
        break;
    case type::CMYK:
        setCMYK();
        break;
    case type::LAB:
        setLAB();
        break;
    case type::HSV:
        setHSV();
        break;
    case type::HLS:
        setHLS();
        break;
    case type::XYZ:
        setXYZ();
        break;
    }
    setSliders();
}

void Module::setRGB(){
    if(le1->text() != color.red()){
    le1->setText(QString::number(color.red()));
    }
    if(le2->text() != color.green()){
    le2->setText(QString::number(color.green()));
    }
    if(le3->text() != color.blue()){
    le3->setText(QString::number(color.blue()));
    }
}

void Module::setCMYK(){
    if(le1->text() != color.cyan()){
        le1->setText(QString::number(color.cyan()));
    }
    if(le2->text() != color.magenta()){
        le2->setText(QString::number(color.magenta()));
    }
    if(le3->text() != color.yellow()){
        le3->setText(QString::number(color.yellow()));
    }
    if(le4->text() != color.black()){
        le4->setText(QString::number(color.black()));
    }
}

void Module::setLAB(){
    double xw = 95.047;
    double yw = 100;
    double zw = 108.883;
    double r = color.red();
    double g = color.green();
    double b = color.blue();
    r/=255;
    b/=255;
    g/=255;
    if(r>0.04045){
        r = pow((r+0.055)/1.055, 2.4);
    }else{
        r/=12.92;
    }
    if(g>0.04045){
        g = pow((g+0.055)/1.055, 2.4);
    }else{
        g/=12.92;
    }
    if(b>0.04045){
        b = pow((b+0.055)/1.055, 2.4);
    }else{
        b/=12.92;
    }
    r*=100;
    g*=100;
    b*=100;
    double x = (int)(r * 0.4124 + g * 0.3576 + b * 0.1805);
    double y = (int)(r * 0.2126 + g * 0.7152 + b * 0.0722);
    double z = (int)(r * 0.0193 + g * 0.1192 + b * 0.9505);
    if(le1->text() != QString::number((int)(116*func2(y/yw) - 16))){
    le1->setText(QString::number((int)(116*func2(y/yw) - 16)));
    }
    if(le2->text() != QString::number((int)(500*(func2(x/xw) - func2(y/yw))))){
    le2->setText(QString::number((int)(500*(func2(x/xw) - func2(y/yw)))));
    }
    if(le3->text() != QString::number((int)(200*(func2(y/yw) - func2(z/zw))))){
    le3->setText(QString::number((int)(200*(func2(y/yw) - func2(z/zw)))));
    }
}

void Module::setXYZ(){
    double r = color.red();
    double g = color.green();
    double b = color.blue();
    r/=255;
    b/=255;
    g/=255;
    if(r>0.04045){
        r = pow((r+0.055)/1.055, 2.4);
    }else{
        r/=12.92;
    }
    if(g>0.04045){
        g = pow((g+0.055)/1.055, 2.4);
    }else{
        g/=12.92;
    }
    if(b>0.04045){
        b = pow((b+0.055)/1.055, 2.4);
    }else{
        b/=12.92;
    }
    r*=100;
    g*=100;
    b*=100;
    int x =(int)(r * 0.4124 + g * 0.3576 + b * 0.1805);
    int y = (int)(r * 0.2126 + g * 0.7152 + b * 0.0722);
    int z = (int)(r * 0.0193 + g * 0.1192 + b * 0.9505);
    if(le1->text() != QString::number(x)){
    le1->setText(QString::number((int)(r * 0.4124 + g * 0.3576 + b * 0.1805)));
    }
    if(le2->text() != QString::number(y)){
    le2->setText(QString::number((int)(r * 0.2126 + g * 0.7152 + b * 0.0722)));
    }
    if(le3->text() != QString::number(z)){
    le3->setText(QString::number((int)(r * 0.0193 + g * 0.1192 + b * 0.9505)));
    }
}

void Module::setHSV(){
    if(le1->text() != QString::number(color.hsvHue())){
    le1->setText(QString::number(color.hsvHue()));
    }
    if(le2->text() != QString::number(color.hsvSaturation())){
    le2->setText(QString::number(color.hsvSaturation()));
    }
    if(le3->text() != QString::number(color.value())){
    le3->setText(QString::number(color.value()));
    }
}

void Module::setHLS(){
    if(color.hslHue()>=0 && le1->text() != QString::number(color.hslHue())){
        le1->setText(QString::number(color.hslHue()));
    }else if(color.hslHue() < 0 && le1->text() != "0"){
        le1->setText("0");
    }
    if(le2->text() != QString::number(color.lightness())){
    le2->setText(QString::number(color.lightness()));
    }
    if(le3->text() != QString::number(color.hslSaturation())){
    le3->setText(QString::number(color.hslSaturation()));
    }
}

QColor Module::colorFromXYZ(double x, double y, double z){
    double r;
    double g;
    double b;
    x/=100;
    y/=100;
    z/=100;
    r = 3.2404542 * x - 0.4985314 * y - 0.4985314 * z;
    g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    b = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    if(r>=0.0031308){
        r = pow(r, 1/2.4)*1.055 - 0.055;
    }else{
        r *=12.92;
    }
    if(g>=0.0031308){
        g = pow(g, 1/2.4)*1.055 - 0.055;
    }else{
        g *=12.92;
    }
    if(b>=0.0031308){
        b = pow(b, 1/2.4)*1.055 - 0.055;
    }else{
        b *=12.92;
    }
    r = (int)(r*255);
    g = (int)(g*255);
    b = (int)(b*255);
    if(r<0){
        r = 0;
        outOfRangeError(413);
    }else if(r>255){
        r = 255;
        outOfRangeError(416);
    }
    if(g<0){
        g = 0;
        outOfRangeError(420);
    }else if(g>255){
        g = 255;
        outOfRangeError(423);
    }
    if(b<0){
        b = 0;
        outOfRangeError(427);
    }else if(b>255){
        b = 255;
        outOfRangeError(430);
    }
    QColor col;
    col.setRgb(r,g,b);
    return col;
}

QColor Module::colorFromLAB(double l, double a, double b){
    double xw = 95.047;
    double yw = 100;
    double zw = 108.883;
    double x = func1(a/500 + ((l+16)/116)) * yw;
    double y = func1((l + 16)/116) * xw;
    double z = func1((l + 16)/116 - b/200) * zw;
    double r;
    double g;
    double bl;
    x/=100;
    y/=100;
    z/=100;
    r = 3.2404542 * x - 0.4985314 * y - 0.4985314 * z;
    g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    bl = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    if(r>=0.0031308){
        r = pow(r, 1/2.4)*1.055 - 0.055;
    }else{
        r *=12.92;
    }
    if(g>=0.0031308){
        g = pow(g, 1/2.4)*1.055 - 0.055;
    }else{
        g *=12.92;
    }
    if(b>=0.0031308){
        b = pow(b, 1/2.4)*1.055 - 0.055;
    }else{
        b *=12.92;
    }
    r = (int)(x*255);
    g = (int)(y*255);
    bl = (int)(z*255);
    if(r<0){
        r = 0;
        outOfRangeError(496);
    }else if(r>255){
        r = 255;
        outOfRangeError(499);
    }
    if(g<0){
        g = 0;
        outOfRangeError(503);
    }else if(g>255){
        g = 255;
        outOfRangeError(506);
    }
    if(bl<0){
        bl = 0;
        outOfRangeError(510);
    }else if(bl>255){
        bl = 255;
        outOfRangeError(513);
    }
    QColor col;
    col.setRgb(r, g, bl);
    return col;
}

double Module::func1(double x) {
    if (x >= 0.008856)
    {
    x = pow(x, 3);
    }
    else
    {
    x = (x - 16/116)/7.787;
    }
    return x;
}

double Module::func2(double x){
    if (x >= 0.008856)
    {
        x = pow(x, 1/3.0);
    }
    else
    {
        x = 7.787*x + 16/116;
    }
    return x;
}
