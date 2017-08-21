#ifndef SERVERTHREADCTRL_H
#define SERVERTHREADCTRL_H

#include <QThread>
#include "serversocket.h"

#define ServerThreadNum 3
#define _DEBUG_ 1

class ServerThreadCtrl : public QThread
{
    Q_OBJECT
public:
    explicit ServerThreadCtrl();
    ~ServerThreadCtrl();
    void TerminalTest();
    void startLoop(int seleType=ServerThreadNum);
    void terminateLoop(int seleType);
    void setCallBack(transterData callback, void * pVoid);

protected:
    void run();

public:
    int _runningNum;

signals:

public slots:

private:
    QThread *_thMsgLoopLaser;
    QThread *_thMsgLoopCmd;
    QThread *_thMsgLoopProg;

    ServerSocket *_serverLaser;
    ServerSocket *_serverCmd;
    ServerSocket *_serverProg;
};

#endif // SERVERTHREADCTRL_H
