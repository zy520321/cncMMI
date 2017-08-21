#include "qmybutton.h"
#include <QMessageBox>

QMyButton::QMyButton(QWidget *parent) :
    QPushButton(parent)
{
    connect(this, SIGNAL(clicked(bool)), SLOT(onClicked(bool)));
}

void QMyButton::onClicked(bool)
{
    QMessageBox::information(this, "tip", text());
}
