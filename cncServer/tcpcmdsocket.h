#ifndef TCPCMDSOCKET_H
#define TCPCMDSOCKET_H

#include "tcpclientsocket.h"

class TcpCmdSocket : public TcpClientSocket
{
    Q_OBJECT

public:
    explicit TcpCmdSocket( bool **connectedState=NULL, QObject *parent = NULL,
                           transterData callBack = NULL, void * pVoid = NULL);
    ~TcpCmdSocket();

private slots:
   virtual void OnReadyRead();

protected:
    void ParseData( const char *data);

private:
    transterData callBackData;
    void * lpVoid;
};

#endif // TCPCMDSOCKET_H
