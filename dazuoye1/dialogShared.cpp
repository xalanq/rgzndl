#include "dialogShared.h"

DialogShared::DialogShared(QWidget *parent) : QDialog(parent)
{
    initValue();
    initUI();
    initConnection();
}

void DialogShared::solve()
{

}

void DialogShared::showAnswer(bool checked)
{
    if (checked) {
        if (Answer.size()) {
            map<string, int> str2ans;
            for (auto i : Answer)
                str2ans[i.data] = i.x;
            for (auto i : Position)
                setValue(i.x, i.y, QString::number(str2ans[i.data]));
        }
    }
    else {
        if (Position.size()) {
            for (auto i : Position)
                setValue(i.x, i.y, QString::fromStdString(i.data));
        }
    }
}

void DialogShared::initValue()
{
    lbls.clear();
    btns.clear();
    layouts.clear();
    btn_solve = new QPushButton(this);
    cbox_display = new QCheckBox(this);
    edit_answer = new QTextEdit(this);
    max_block = 1;
    rows = 1;
}

void DialogShared::initUI()
{
    initTheButton(btn_solve);
    btn_solve->setText(tr("Solve!!"));
    btn_solve->setFixedHeight(50);
    cbox_display->setText("&Show");
    cbox_display->setFixedWidth(100);
    cbox_display->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    edit_answer->setReadOnly(true);
    edit_answer->setFixedWidth(100);
    edit_answer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    edit_answer->setStyleSheet(" \
        QTextEdit { \
            font-size: 20px; \
        } \
        QScrollBar:vertical { \
            width:15px; \
        }"
    );

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
}

void DialogShared::initConnection()
{
    connect(btn_solve, SIGNAL(clicked(bool)),
            this, SLOT(solve()));
    connect(cbox_display, SIGNAL(clicked(bool)),
            this, SLOT(showAnswer(bool)));
}

void DialogShared::initTheWidgetSize(QWidget *widget)
{
    widget->setFixedSize(QSize(50, 50));
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void DialogShared::initTheLayout(QLayout *layout)
{
    layout->setContentsMargins(0, 0, 0, 0);
}

void DialogShared::initTheButton(QPushButton *btn)
{
    btn->setStyleSheet(" \
        QPushButton { \
            border: 1px solid #8f8f91; \
            border-radius: 10px; \
            background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                         stop: 0 #f6f7fa, stop: 1 #dadbde); \
        } \
        QPushButton:pressed { \
            background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                         stop: 0 #dadbde, stop: 1 #f6f7fa); \
        } \
        QPushButton:flat { \
            border: none;  */ \
        } \
        QPushButton:default { \
            border-color: navy; \
        }"
    );
}

void DialogShared::setValue(int x, int y, const QString &str)
{
    int len = layouts[x]->count();
    auto block = (BlockEdit *)(layouts[x]->itemAt(len - 1 - y)->widget());
    block->setText(str);
}

BlockEdit *DialogShared::newBlockEdit(int x, int y)
{
    BlockEdit *ret = new BlockEdit(x, y, this);
    ret->installEventFilter(this);
    return ret;
}

bool DialogShared::eventFilter(QObject *watched, QEvent *event)
{
    if (event && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent) {
            if (keyEvent->key() == Qt::Key_Tab || keyEvent->key() == Qt::Key_Backtab) {
                auto widget = dynamic_cast<BlockEdit *> (focusWidget());
                if (widget) {
                    int x = widget->X(), y = layouts[x]->count() - 1 - widget->Y();
                    if (keyEvent->key() == Qt::Key_Backtab) {
                        if (y == 1) {
                            x = (x + rows - 1) % rows;
                            y = layouts[x]->count() - 1;
                        }
                        else
                            y--;
                    }
                    else {
                        if (y == layouts[x]->count() - 1) {
                            x = (x + 1) % rows;
                            y = 1;
                        }
                        else
                            y++;
                    }
                    layouts[x]->itemAt(y)->widget()->setFocus();
                    return true;
                }
            }
        }
    }
    return QDialog::eventFilter(watched, event);
}
