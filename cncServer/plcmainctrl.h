#ifndef PLCMAINCTRL_H
#define PLCMAINCTRL_H

#include <QThread>

class PLCMainCtrl : public QThread
{
    Q_OBJECT
public:
    explicit PLCMainCtrl(QObject *parent = 0);

protected:
    void run();

signals:

public slots:

};

#endif // PLCMAINCTRL_H
