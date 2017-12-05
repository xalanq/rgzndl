#include "widgetPlus.h"

widgetPlus::widgetPlus(QWidget *parent) : QWidget(parent)
{

    initValue();
    initUI();
    initConnection();
}

void widgetPlus::initValue()
{
    lbl_plus = new QLabel("+");
    btn_add_1 = new QPushButton(tr("Add"));
    btn_add_2 = new QPushButton(tr("Add"));
    btn_add_3 = new QPushButton(tr("Add"));
}

void widgetPlus::initUI()
{

}

void widgetPlus::initConnection()
{

}
