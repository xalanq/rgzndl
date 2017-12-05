#ifndef WIDGETPLUS_H
#define WIDGETPLUS_H

#include "header.h"
#include "dialogChoose.h"
#include "blockEdit.h"
#include "solver.h"

class WidgetPlus : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPlus(QWidget *parent = nullptr);

signals:

public slots:
    void addBlock(int id);
    void solve();

private:
    QLabel *lbl_line;
    QList<QLabel *> lbls;
    QList<PushButtonID *> btns;
    QList<QHBoxLayout *> layouts;
    QPushButton *btn_solve;
    QCheckBox *cbox_display;
    QTextEdit *edit_answer;
    int max_block;

    void initValue();
    void initUI();
    void initConnection();

    void initTheWidgetSize(QWidget *widget);
    void initTheLayout(QLayout *layout);
    void initTheButton(QPushButton *btn);
};

#endif // WIDGETPLUS_H
