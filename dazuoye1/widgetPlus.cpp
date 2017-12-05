#include "widgetPlus.h"

WidgetPlus::WidgetPlus(QWidget *parent) : QWidget(parent)
{

    initValue();
    initUI();
    initConnection();
}

void WidgetPlus::addBlock(int id)
{
    layouts[id]->insertWidget(1, new BlockEdit(this));
    if (layouts[id]->count() > max_block) {
        max_block = layouts[id]->count();
        setMinimumWidth(std::max(515, 515 + 59 * (max_block - 5)));
    }
}

void WidgetPlus::initValue()
{
    lbls.clear();
    btns.clear();
    layouts.clear();
    for (int i = 0; i < 3; ++i) {
        lbls.append(new QLabel(this));
        btns.append(new PushButtonID(i, this));
        layouts.append(new QHBoxLayout);
    }
    lbl_line = new QLabel(this);
    btn_solve = new QPushButton(this);
    cbox_display = new QCheckBox(this);
    edit_answer = new QTextEdit(this);
    max_block = 1;
}

void WidgetPlus::initUI()
{
    for (int i = 0; i < 3; ++i) {
        initTheButton(btns[i]);
        initTheWidgetSize(btns[i]);
        btns[i]->setText(tr("Add"));
        initTheWidgetSize(lbls[i]);
        layouts[i]->addStretch();
        layouts[i]->addWidget(new BlockEdit(this));
    }
    lbls[1]->setText("<p style='font-size:50px; font-weight:bold'>+</p>");
    lbl_line->setMaximumHeight(2);
    lbl_line->setStyleSheet("background-color: #c0c0c0");
    initTheButton(btn_solve);
    btn_solve->setText(tr("Solve!!"));
    btn_solve->setFixedHeight(50);
    cbox_display->setText("&Show Answer");
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

    auto layout_left = new QVBoxLayout;
    auto layout_mid = new QVBoxLayout;
    auto layout_right = new QVBoxLayout;
    auto layout_up = new QHBoxLayout;
    auto layout_down = new QHBoxLayout;
    auto layout_edit = new QVBoxLayout;
    auto layout_display = new QVBoxLayout;
    auto layout = new QHBoxLayout;

    initTheLayout(layout_left);
    initTheLayout(layout_mid);
    initTheLayout(layout_right);
    initTheLayout(layout_up);
    initTheLayout(layout_down);

    layout_left->addWidget(lbls[0]);
    layout_left->addWidget(lbls[1]);

    layout_mid->addLayout(layouts[0]);
    layout_mid->addLayout(layouts[1]);

    layout_right->addWidget(btns[0]);
    layout_right->addWidget(btns[1]);

    layout_up->addLayout(layout_left);
    layout_up->addLayout(layout_mid);
    layout_up->addLayout(layout_right);

    layout_down->addWidget(lbls[2]);
    layout_down->addLayout(layouts[2]);
    layout_down->addWidget(btns[2]);

    layout_edit->addLayout(layout_up);
    layout_edit->addWidget(lbl_line);
    layout_edit->addLayout(layout_down);
    layout_edit->addWidget(btn_solve);

    layout_display->addWidget(cbox_display);
    layout_display->addWidget(edit_answer);

    layout->addLayout(layout_edit);
    layout->addSpacing(25);
    layout->addLayout(layout_display);

    setLayout(layout);

    setMinimumWidth(515);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
}

void WidgetPlus::initConnection()
{
    for (auto i : btns)
        connect(i, SIGNAL(myClicked(int)),
                this, SLOT(addBlock(int)));
}

void WidgetPlus::initTheLayout(QLayout *layout)
{
    layout->setContentsMargins(0, 0, 0, 0);
}

void WidgetPlus::initTheButton(QPushButton *btn)
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

void WidgetPlus::initTheWidgetSize(QWidget *widget)
{
    widget->setFixedSize(QSize(50, 50));
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
