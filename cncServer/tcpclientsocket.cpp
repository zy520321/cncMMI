#include "tcpclientsocket.h"
#include <QObject>
#include <QtNetwork/QHostAddress>
#include <QtWidgets/QMessageBox>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <QtGui/QInputMethod>
#include <QCoreApplication>
#include <stdio.h>

TcpClientSocket::TcpClientSocket( bool **connectedState, QObject *parent /* = NULL */, transterData callBack, void *pVoid):
    QTcpSocket( parent )
{
    connect( this, SIGNAL(readyRead()), this, SLOT(OnReadyRead()) );
    connect( this, SIGNAL(connected()), this, SLOT(OnConnected()) );
    connect( this, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
    connect( this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnError(QAbstractSocket::SocketError )));
    connect( this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(OnStateChanged(QAbstractSocket::SocketState)));

    _id=123456;
    _isConnected=false;
    *connectedState=&_isConnected;
}

TcpClientSocket::~TcpClientSocket()
{
    if(_isConnected)
        Close();
}

void TcpClientSocket::connectToServer( const char *ip, quint16 port )
{
    QString strip( ip );
    QHostAddress addr;
    addr.setAddress( strip );
    connectToHost( addr, port );
    waitForConnected( 1000 );

#ifdef Q_OS_LINUX
    //KeepAlive
    int enableKeepAlive = 1;
    int fd = socketDescriptor();
    setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE,&enableKeepAlive,sizeof(enableKeepAlive));

    int maxIdle = 10;// seconds
    setsockopt(fd,IPPROTO_TCP,TCP_KEEPIDLE,&maxIdle,sizeof(maxIdle));

    int count = 3; //发送多达3个keepalive包，如果没有响应则断开
    setsockopt(fd,SOL_TCP,TCP_KEEPCNT,& count,sizeof(count));

    int interval = 2; //每隔2秒发送一个keepalive包（在5秒的空闲时间之后）
    setsockopt(fd,SOL_TCP,TCP_KEEPINTVL,& interval,sizeof(interval));
#endif
}

void TcpClientSocket::Close()
{
    disconnectFromHost();
    close();
}
void TcpClientSocket::slotWriteMsg(const char *msg)
{
    sendData(msg,strlen(msg)+1);
}
void TcpClientSocket::slotWriteMsg(QString msg)
{

}
bool TcpClientSocket::sendData( const char *data, qint64 len )
{
    if( NULL == data || len <= 0 )
        return false;
    qint64 ret = writeData( data, len );
    if( 0 >= ret )
       return false;
    waitForBytesWritten(4);
    qDebug( "send    data: %s\n", data );
    flush();
    //waitForReadyRead( -1 );                     // why ?
    return true;
}
void TcpClientSocket::ParseData( const char *data)
{
}
void TcpClientSocket::OnReadyRead()
{
  //  qDebug("TcpClientSocket:read file..._transmissionType(%d)\n", _transmissionType);
    char data[BUFFERSIZE_MAX] = { 0 };
    while(bytesAvailable()>0)
    {
         if(isValid())
         {
             QByteArray temp = readAll();
             if(temp=="")
                 break;
             strcat(data,temp.data());
         }
         else
         {
             break;
         }
    }
//    qDebug( "Res: %s from %d\n", data ,_id);
    _resMsg=data;
    ParseData(data);
    emit signalResMsg(_resMsg);
}
void  TcpClientSocket::SetSignId(qintptr id)
{
    _id=id;
    setSocketDescriptor(id);
#ifdef Q_OS_LINUX
    //KeepAlive
    int enableKeepAlive = 1;
    int fd = id;//socketDescriptor();
    setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE,&enableKeepAlive,sizeof(enableKeepAlive));

    int maxIdle = 10;// seconds
    setsockopt(fd,IPPROTO_TCP,TCP_KEEPIDLE,&maxIdle,sizeof(maxIdle));

    int count = 3; //发送多达3个keepalive包，如果没有响应则断开
    setsockopt(fd,SOL_TCP,TCP_KEEPCNT,& count,sizeof(count));

    int interval = 2; //每隔2秒发送一个keepalive包（在5秒的空闲时间之后）
    setsockopt(fd,SOL_TCP,TCP_KEEPINTVL,& interval,sizeof(interval));
#endif
}
void TcpClientSocket::OnConnected()
{
    _isConnected=true;
    qDebug( "connected: %d !\n", socketDescriptor() );
}
void TcpClientSocket::OnDisconnected()
{
    _isConnected=false;
    qDebug( "Disconnected: %d !\n", socketDescriptor() );
    emit signalDisconneted(_id);
}
void TcpClientSocket::OnError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug("Fortune Client: Romote server closed illegally.\n");
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug("Fortune Client: The host was not found,Please check the host name and port settings.\n");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug("Fortune Client: The connection was refused by the peer,Make sure the fortune server is running and check that the host name and port settings are correct.\n");
        break;
    case QAbstractSocket::SocketTimeoutError:
        qDebug("Fortune Client: The host was not found,The socket operation timed out.\n");
        break;
    default:
        QString msg="Fortune Client: ";
        msg+=QObject::tr("The following error occurred: %1.").arg(this->errorString());
        msg+="\n";
        qDebug(msg.toLatin1().data());
        break;
    }
    emit signalError(socketError,_id);
}
void TcpClientSocket::OnStateChanged(QAbstractSocket::SocketState eSocketState)
{
    switch(eSocketState)
    {
    case QAbstractSocket::HostLookupState:
    case QAbstractSocket::ConnectingState:
        break;
    case QAbstractSocket::ConnectedState:
        break;
    case QAbstractSocket::ClosingState:
        break;
    case QAbstractSocket::UnconnectedState:

        break;
    default:
        break;
    }
}
