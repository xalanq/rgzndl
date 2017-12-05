#include "blockEdit.h"

BlockEdit::BlockEdit(QWidget *parent) : QLineEdit(parent)
{
    initUI();
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

