#ifndef QMYLABEL_H
#define QMYLABEL_H

#include <QLabel>

class QMyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QMyLabel(QWidget *parent = 0);

signals:
    void clickedLabel(bool);

public slots:

protected:
    void mouseReleaseEvent(QMouseEvent *ev);

};

#endif // QMYLABEL_H
