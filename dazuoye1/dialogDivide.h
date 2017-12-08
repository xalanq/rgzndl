#ifndef DIALOGDIVIDE_H
#define DIALOGDIVIDE_H

#include "dialogShared.h"

class DialogDivide : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDivide(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initValue();
    void initUI();
    void initConnection();
};

#endif // DIALOGDIVIDE_H
