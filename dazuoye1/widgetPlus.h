#ifndef WIDGETPLUS_H
#define WIDGETPLUS_H

#include "header.h"

class widgetPlus : public QWidget
{
    Q_OBJECT

public:
    explicit widgetPlus(QWidget *parent = nullptr);

signals:

public slots:

private:
    QLabel *lbl_plus;
    QPushButton *btn_add_1, *btn_add_2, *btn_add_3;

    void initValue();
    void initUI();
    void initConnection();
};

#endif // WIDGETPLUS_H
