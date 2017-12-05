#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "header.h"
#include "widgetPlus.h"
#include "solver.h"

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
