#include "dialogTimes.h"

DialogTimes::DialogTimes(QWidget *parent) : DialogShared(parent)
{
    initValue();
    initUI();
    initConnection();
}

void DialogTimes::addBlock(int id)
{

}

void DialogTimes::solve()
{

}

void DialogTimes::initValue()
{
    lbl_line1 = new QLabel(this);
    lbl_line2 = new QLabel(this);
}

void DialogTimes::initUI()
{
    lbl_line1->setMaximumHeight(2);
    lbl_line1->setStyleSheet("background-color: #c0c0c0");
    lbl_line2->setMaximumHeight(2);
    lbl_line2->setStyleSheet("background-color: #c0c0c0");
}

void DialogTimes::initConnection()
{

}
