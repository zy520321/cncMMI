#include "serversocket.h"
#include "tcpfilesocket.h"
#include "tcpcmdsocket.h"

ServerSocket::ServerSocket(bool isFileCtrl,int port,QObject *parent) :
    QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
    tcpClientSocket = NULL;
    _accept = false;
    _isFileCtrl = isFileCtrl;
}
ServerSocket::~ServerSocket()
{
    if (tcpClientSocketList.size() > 0)
    {
        for (int i = 0; i<tcpClientSocketList.count(); i++)
        {
            QTcpSocket *item = tcpClientSocketList.at(i);
            item->close();
        }
    }
    else if (tcpClientSocket)
        tcpClientSocket->close();
}

void ServerSocket::setCallBack(transterData callback, void * pVoid)
{
    callBackData = callback;
    lpVoid = pVoid;
}

void ServerSocket::socket_Read_Data()
{
    QString str;
    QByteArray buffer;
    int iBytesAvailable = tcpClientSocket->bytesAvailable();

    while (--iBytesAvailable >= 0)
    {
        if (tcpClientSocket->isValid())
        {
            buffer = tcpClientSocket->readAll();
            if (buffer == "")
                break;
            str += buffer;
        }
        else
        {
            break;
        }
    }

    if (str.size()>0)
        emit signalSendResMsg(str);
}

void ServerSocket::socket_Disconnected()
{
    _accept = false;
    emit isDisConnected();
    qDebug() << "Disconnected!";
}
void ServerSocket::incomingConnection(qintptr handle)
{
    qDebug("Accept Client: %d, theadid=%x, line=%d...\n",handle, QThread::currentThreadId(), __LINE__);
    if (_accept)
        return;
    _accept = true;
    bool *clientState=NULL;
    TcpClientSocket *tcpClientSocket;
    if(_isFileCtrl)
    {
        qDebug("Accept Client: %d, line=%d...\n",handle, __LINE__);
        TcpFileSocket *tcpFileSocket = new TcpFileSocket(&clientState,this);
        tcpClientSocket=tcpFileSocket;
    }
    else
    {
        qDebug("Accept Client: %d, line=%d...\n",handle, __LINE__);
        TcpCmdSocket *tcpCmdSocket = new TcpCmdSocket(&clientState,this, callBackData, lpVoid);
        tcpClientSocket=tcpCmdSocket;
    }
    clientStateList.push_back(clientState);
    connect(tcpClientSocket,SIGNAL(signalResMsg(QString)),this,SIGNAL(signalSendResMsg(QString)));
    connect(tcpClientSocket,SIGNAL(signalDisconneted(qintptr)),this,SLOT(slotDisconnected(qintptr)));
    connect(tcpClientSocket,SIGNAL(signalError(QAbstractSocket::SocketError,qintptr)),this,SLOT(slotError(QAbstractSocket::SocketError,qintptr)));

    tcpClientSocket->SetSignId(handle);
    tcpClientSocketList.append(tcpClientSocket);
  //  tcpClientSocket->write("Wellcome connect server");
    qDebug("Accept Client: %d, isFileClient(%d)\n",handle, _isFileCtrl);
    emit getNewClient(handle);
}
void ServerSocket::updateClients(char* msg, int length)
{
    QString smsg(msg);
    updateClients(smsg,length);
}
void ServerSocket::updateClients(QString msg, int length)
{
    if (tcpClientSocketList.size() > 0)
    {
        for (int i = 0; i<tcpClientSocketList.count(); i++)
        {
            QTcpSocket *item = tcpClientSocketList.at(i);
            if (item->write(msg.toLatin1(), length) != length)
            {
                continue;
            }
        }
    }
    else if (tcpClientSocket)
    {
        tcpClientSocket->write(msg.toLatin1(), length);
    }
}
void ServerSocket::slotDisconnected(qintptr descriptor)
{
    _accept = false;
    for (int i=0;i<tcpClientSocketList.count();i++)
    {
        if(tcpClientSocketList.at(i)->getId()==descriptor)
        {
            TcpClientSocket *tcpClientSocket =tcpClientSocketList.at(i);
            disconnect(tcpClientSocket,SIGNAL(signalResMsg(QString)),this,SIGNAL(signalSendResMsg(QString)));
            disconnect(tcpClientSocket,SIGNAL(signalDisconneted(qintptr)),this,SLOT(slotDisconnected(qintptr)));
            disconnect(tcpClientSocket,SIGNAL(signalError(QAbstractSocket::SocketError,qintptr)),this,SLOT(slotError(QAbstractSocket::SocketError,qintptr)));
            tcpClientSocket->close();
            tcpClientSocketList.removeAt(i);
            qDebug("%d Disconnected!\n",descriptor);
            emit isDisConnected();
            return;
        }
    }
    return;
}
void ServerSocket::slotError(QAbstractSocket::SocketError err,qintptr id)
{

}
