#include "tcpcmdsocket.h"
#include <QThread>

TcpCmdSocket::TcpCmdSocket( bool **connectedState, QObject *parent /* = NULL */, transterData callBack, void * pVoid):
    TcpClientSocket( connectedState, parent, callBack, pVoid )
{
    connect(this, SIGNAL(signalResMsg(const char *)), this, SLOT(slotWriteMsg(const char *)));

    callBackData = callBack;
    lpVoid = pVoid;
}
TcpCmdSocket::~TcpCmdSocket()
{
    close();
}

void TcpCmdSocket::OnReadyRead()
{
    qDebug("TcpCmdSocket:thread id=%x...\n", QThread::currentThreadId);

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
    //qDebug( "Res: %s from %d\n", data ,_id);
   // qDebug("-------------recv--------\n");

    _resMsg=data;
    ParseData(data);
 //   emit signalResMsg(_resMsg);
}

void TcpCmdSocket::ParseData( const char *data)
{
    int size = strlen(data);
    int ret = 0;
    char buf[BUFFERSIZE_MAX] = { 0 };

    int counts = getPacketCounts(size);
    ADDR_INFO * newData = new ADDR_INFO[counts];

    ret = analyze(data, size, newData, counts);
    if (ret < 0)
    {
        delete [] newData;
        newData = NULL;
        //发送错误信息
        return ;
    }
    if (NULL != callBackData)
    {
        ret = callBackData(newData, counts, lpVoid);
        if (ret < 0)
        {
            //
            //发送错误信息
            delete [] newData;
            newData = NULL;
            return ;
        }
    }

    size = BUFFERSIZE_MAX;
    ret = encapsulate(newData, counts, buf, size, true);
    if (ret < 0)
    {
        //
        //发送错误信息
        delete [] newData;
        newData = NULL;
        return ;
    }
    //send data??
    //sendData(buf, ret);

    delete [] newData;
    newData = NULL;
    slotWriteMsg(buf);
    //emit signalResMsg(buf);
}

