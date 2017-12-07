#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "header.h"
#include "dialogPlusMinus.h"
#include "dialogTimes.h"
#include "dialogDivide.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initValue();
    void initUI();
    void initConnection();

    void actionAbout();

    void workPlus();
    void workMinus();
    void workTimes();
    void workDivide();

    void welcome();
};

#endif // MAINWINDOW_H
