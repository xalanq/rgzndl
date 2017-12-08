#include "dialogDivide.h"

DialogDivide::DialogDivide(QWidget *parent) : QDialog(parent)
{
    initValue();
    initUI();
    initConnection();
}

void DialogDivide::initValue()
{

}

void DialogDivide::initUI()
{
    QLabel *lbl = new QLabel(this);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setText("<p>除法太灵活了</p><p><b>很(bu)难(xiang)写(xie)!</b></p><p>所以就不写了吧QAQ</p><p>反正也就是搜搜搜</p>");
    QLayout *layout = new QVBoxLayout;
    layout->addWidget(lbl);
    setLayout(layout);
    setFixedWidth(300);
    setFixedHeight(200);
}

void DialogDivide::initConnection()
{

}
