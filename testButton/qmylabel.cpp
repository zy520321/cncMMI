#include "qmylabel.h"
#include <QMouseEvent>

QMyLabel::QMyLabel(QWidget *parent) :
    QLabel(parent)
{
  //  connect(this, SIGNAL(clickedLabel()), SLOT(lableClicked()));
}

void QMyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        emit clickedLabel(true);
        ev->ignore();
    }
}
