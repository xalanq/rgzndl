#include "blockEdit.h"

BlockEdit::BlockEdit(int _x, int _y, QWidget *parent) : QLineEdit(parent)
{
    x = _x;
    y = _y;
    initUI();
}

int BlockEdit::X()
{
    return x;
}

int BlockEdit::Y()
{
    return y;
}

void BlockEdit::initUI()
{
    setTextMargins(1, 1, 1, 1);
    setAlignment(Qt::AlignCenter);
    setFixedSize(QSize(50, 50));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setValidator(new QRegExpValidator(QRegExp("\\S{0,1}")));
    setStyleSheet(" \
        QLineEdit { \
            font-size: 30px; \
            border: 1px solid gray; \
            border-radius: 10px; \
            padding: 0px; \
            selection-background-color: darkgray; \
        }"
    );
}

