#ifndef QMYBUTTON_H
#define QMYBUTTON_H

#include <QPushButton>

class QMyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QMyButton(QWidget *parent = 0);

signals:

public slots:
    void onClicked(bool);

};

#endif // QMYBUTTON_H
