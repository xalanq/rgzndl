#include "dialogChoose.h"


PushButtonID::PushButtonID(int id, QWidget *parent) : QPushButton(parent)
{
    ID = id;
    connect(this, SIGNAL(clicked(bool)),
            this, SLOT(slot_myClicked()));
}

void PushButtonID::slot_myClicked()
{
    emit myClicked(ID);
}

DialogChoose::DialogChoose(const QList<QString> &list, QWidget *parent) : QDialog(parent)
{
    answer = -1;

    setUI(list);
    setConnection();
}

int DialogChoose::getAnswer()
{
    return answer;
}

void DialogChoose::setUI(const QList<QString> &list)
{

    QVBoxLayout *layout = new QVBoxLayout;
    for (int i = 0; i < list.length(); ++i)
    {
        PushButtonID *button = new PushButtonID(i);
        button->setText(list[i]);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        button->setFixedHeight(50);
        button->setStyleSheet(" \
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

        connect(button, SIGNAL(myClicked(int)),
                this, SLOT(myAccept(int)));
        layout->addWidget(button);
    }
    QWidget *widget = new QWidget;
    layout->addStretch();
    widget->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);
    QScrollArea *area =	new QScrollArea;

    area->setContentsMargins(0, 0, 0, 0);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    area->setWidget(widget);
    area->setWidgetResizable(true);
    area->setFrameShape(QFrame::NoFrame);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(area);
    setLayout(main_layout);
    setMinimumWidth(250);
    setMaximumWidth(250);
    setMinimumHeight(60);
    setMaximumHeight(600);
    resize(250, list.length() * (68 - list.length()));
}

void DialogChoose::setConnection()
{

}

void DialogChoose::myAccept(int id)
{
    answer = id;
    QDialog::accept();
}
