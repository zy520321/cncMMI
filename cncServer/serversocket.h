#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QTcpServer>
#include <QStringList>
#include "tcpclientsocket.h"

class ServerSocket : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerSocket(bool isFileCtrl=false,int port=0,QObject *parent = 0);
    ~ServerSocket();
    QList<TcpClientSocket*> tcpClientSocketList;
    QList<bool *> clientStateList;
    QTcpSocket* tcpClientSocket;
public:
    void setCallBack(transterData callback, void * pVoid);

signals:
    void updateServer(QString,int);
    void signalSendResMsg(QString msg);
    void getNewClient(int id);
    void isDisConnected();

public slots:
    void updateClients(char* msg, int length);
    void updateClients(QString msg, int length);
    void slotDisconnected(qintptr descriptor);
    void slotError(QAbstractSocket::SocketError err,qintptr id);

    void socket_Disconnected();
    void socket_Read_Data();

protected:
    void incomingConnection(qintptr handle);

private:
    QStringList fortunes;
    int onlineDescriptor;
    bool _isFileCtrl;
    bool _accept;

    transterData callBackData;
    void * lpVoid;
};

#endif // SERVERSOCKET_H
