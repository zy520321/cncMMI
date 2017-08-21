#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QtNetwork/QTcpSocket>
#include <QFile>
#include "protocol/analyzeEncapsulate.h"


class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    explicit TcpClientSocket  ( bool **connectedState=NULL, QObject *parent = NULL,
                                transterData callBack = NULL, void *pVoid = NULL);
    ~TcpClientSocket          ();

    void    connectToServer   ( const char *ip, quint16 port );
    void    Close             ();
    bool    sendData         ( const char *data, qint64 len );
    void    SetSignId         (qintptr id);
    qintptr getId             (){return _id;};

signals:
    void    signalResMsg(const char * msg);
    void    signalResMsg(QString msg);
    int     signalDisconneted (qintptr id);
    void    signalError       (QAbstractSocket::SocketError err,qintptr id);

protected:
    virtual void ParseData   ( const char *data);

public slots:
    void    slotWriteMsg      ( const char *msg);
    void    slotWriteMsg      (QString msg);

private slots:
    void    OnConnected       ();
    virtual void OnReadyRead  ();
    void    OnDisconnected    ();
    void    OnError           (QAbstractSocket::SocketError socketError);
    void    OnStateChanged    (QAbstractSocket::SocketState eSocketState);

protected:
    enum { BUFFERSIZE_MAX = 1024 };
    QString _resMsg;
    qintptr _id;
    bool _isConnected;
    unsigned int _transmissionType;
};

#endif // TCPCLIENTSOCKET_H
