#ifndef BLOCKEDIT_H
#define BLOCKEDIT_H

#include "header.h"

class BlockEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit BlockEdit(int x, int y, QWidget *parent = nullptr);

    int X();
    int Y();

signals:

public slots:

private:
    void initUI();
    int x, y;
};

#endif // BLOCKEDIT_H
