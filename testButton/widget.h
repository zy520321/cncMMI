#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qmylabel.h"
#include "qmybutton.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QMyLabel * myLabel;
    QMyButton * btn;
};

#endif // WIDGET_H
