#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    btn = new QMyButton(this);
    btn->setObjectName("btnTest");
    //btn->setText("hello");
    btn->setGeometry(0, 0, 50, 50);

    myLabel = new QMyLabel(btn);
    myLabel->setObjectName("test");
    myLabel->setText("test");
    myLabel->setGeometry(0,0,50,30);
    myLabel->setAlignment(Qt::AlignCenter);

    connect(myLabel, SIGNAL(clickedLabel(bool)), btn, SLOT(onClicked(bool)));
}

Widget::~Widget()
{
    delete ui;
}
