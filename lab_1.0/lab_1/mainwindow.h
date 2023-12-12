#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "module.h"
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setwColor();

private slots:
    void on_pbColor_clicked();
    void changeColor1();
    void changeColor2();
    void changeColor3();
    void on_actionRGB_LAB_CMYK_triggered();

    void on_actionCMYK_RGB_HSV_triggered();

    void on_actionRGB_XYZ_CMYK_triggered();

    void on_actionRGB_CMYK_HLS_triggered();

    void on_actionRGB_XYZ_HSV_triggered();

    void on_actionCMYK_LAB_XYZ_triggered();

    void on_actionRGB_XYZ_LAB_triggered();

    void on_actionHSV_XYZ_LAB_triggered();

    void on_actionRGB_CMYK_HSV_triggered();

    void on_action_RGB_HSV_LAB_triggered();

    void on_actionCMYK_LAB_RGB_triggered();

    void on_actionCMYK_HLS_XYZ_triggered();

    void on_actionCMYK_LAB_HSV_triggered();

    void on_actionXYZ_LAB_HLS_triggered();

    void on_actionRGB_HLS_LAB_triggered();

    void on_actionCMYK_RGB_HLS_triggered();

    void on_actionRGB_XYZ_HLS_triggered();

    void on_actionCMYK_XYZ_RGB_triggered();

private:
    void setColors();
    Ui::MainWindow *ui;
    Module* m1 = new Module;
    Module* m2 = new Module;
    Module* m3 = new Module;
    QWidget* wColor = new QWidget;
    QPushButton* pbColor = new QPushButton;
    QColor color;
};
#endif // MAINWINDOW_H
