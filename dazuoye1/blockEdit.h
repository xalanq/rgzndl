#ifndef BLOCKEDIT_H
#define BLOCKEDIT_H

#include "header.h"

class BlockEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit BlockEdit(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();
};

#endif // BLOCKEDIT_H
