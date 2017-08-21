#include "tcpfilesocket.h"
#include "ncprogpreprocess.h"

#include <QObject>
#include <QtNetwork/QHostAddress>
#include <QtWidgets/QMessageBox>

TcpFileSocket::TcpFileSocket( bool **connectedState, QObject *parent /* = NULL */ ):
    TcpClientSocket( connectedState,parent )
{
    connect( this, SIGNAL(signalSendFile(QString)), this, SLOT(SendFileHead(QString)));
    connect( this, SIGNAL(signalSendFileContent()), this, SLOT(SendFileContent()));
    _byteReceived=0;
    _transmissionType = 0;
}
TcpFileSocket::~TcpFileSocket()
{

}
void TcpFileSocket::ParseData( const char *data)
{
    if(strcmp(data,S_FILL_READ)==0)
    {
        _transmissionType=FILL_READ_TYPE;
    }
    else if(strcmp(data,S_FILL_WRITE)==0)
    {
        _transmissionType=FILL_WRITE_TYPE;
        _byteReceived=0;
    }
    else if(strcmp(data,S_FILL_WRITE_ACK)==0)
    {
        emit signalSendFileContent();
    }
}
void TcpFileSocket::OnReadyRead()
{
    qDebug("TcpFileSocket:OnReadyRead, thread id=%x...\n", QThread::currentThreadId);

    if(_transmissionType==FILL_READ_TYPE)
        _transmissionType=FILL_READ_NAME_TYPE;
    else if(_transmissionType==FILL_WRITE_TYPE)
    {
        OnReadyReceiveFile();
        return;
    }

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
    qDebug( "file Res: %s from %d\n", data ,_id);
    _resMsg=data;
    ParseData(data);
}
void TcpFileSocket::OnReadyReceiveFile()
{
    static int lastRate=-1;
    if(_byteReceived == 0)  //才刚开始接收数据，此数据为文件信息
    {
        _inBlock = this->readAll();
        int length=_inBlock.size();
        bool hasReadSize=false,hasReadName=false;
        char get[1024],cur,last=1;

        for(int i=0,j=0; i<length; i++)
        {
            cur=_inBlock.at(i);
            if(!hasReadSize)
            {
                if(cur>='0'&&cur<='9')
                    get[j++]=cur;
                else if(j>0)
                {
                    get[j]=0;
                    _totalSize=atoi(get);
                    j=0;
                    hasReadSize=true;
                }
            }
            else if(!hasReadName)
            {
                if(cur>=32)
                {
                   get[j++]=cur;
                }
                else if(j>0&&last==0&&cur==0)
                {
                    get[j]=0;
                    _fileName=get;
                    j=0;
                    hasReadName=true;
                    break;
                }
                last=cur;
            }
        }
        _fileName.sprintf("%s", "/home/sibonac/workspace/111111.txt");

        _newFile = new QFile(_fileName);
        _newFile->open(QFile::WriteOnly);
        qDebug("Is receiving a file : %s size %d\n",_fileName.toLatin1().data(),_totalSize);
        _byteReceived=1;
        slotWriteMsg(S_FILL_WRITE_ACK);
    }
    else  //正式读取文件内容
    {
        _inBlock = this->readAll();

        _byteReceived += _inBlock.size();
        _newFile->write(_inBlock);
        _newFile->flush();
        int curRate=_byteReceived*100/_totalSize;
        if(curRate!=lastRate)
        {
            lastRate=curRate;
        }
    }

    if(_byteReceived >= _totalSize)
    {
        qDebug("File <%s> receive complete as size %d!\n",_fileName.toLatin1().data(),_byteReceived);

        _newFile->close();
        _inBlock.clear();
        _byteReceived = 0;
        _totalSize = 0;
        _transmissionType=0;
        lastRate=-1;
    }
}
void TcpFileSocket::OnGetFile(QString fileName)
{
    char sendFileCMd[64]=S_FILL_READ;
    slotWriteMsg(sendFileCMd);
    usleep(50);
    slotWriteMsg(fileName.toLatin1().data());
}
void TcpFileSocket::OnSendFile(QString fileName)
{
    char sendFileCMd[64]=S_FILL_WRITE;
    slotWriteMsg(sendFileCMd);
    usleep(50);

    emit signalSendFile(fileName);
}

void TcpFileSocket::SendFileContent()
{
    while(!_needTerminateSend)
    {
        if(GoOnSend(_loadSize))
            break;
        usleep(100);
    }
    if(_needTerminateSend)
        _localFile->close();
}
void TcpFileSocket::SendFileHead(QString fileName)  //发送文件头信息
{
    _fileName=fileName;
    //_fileName="Files/" + fileName;

    _localFile = new QFile(_fileName);
    _localFile->open(QFile::ReadOnly);
    _startSendFlag=false;

    _byteToWrite = _localFile->size();  //剩余数据的大小
    _totalSize = _localFile->size();

    _loadSize = 4*1024;  //每次发送数据的大小

    QString currentFileName = _fileName;//.right(_fileName.size() - _fileName.lastIndexOf('/')-1);
    char tempS[64];
    sprintf(tempS,"%d",_totalSize);

    QDataStream out(&_outBlock, QIODevice::WriteOnly);
    out<<tempS;//<<qint64(_outBlock.size());
    out<<qint64(0)<<qint64(0)<<currentFileName;
    out<<qint64(0)<<qint64(0)<<"END";

    write(_outBlock);  //将读到的文件发送到套接字
    waitForBytesWritten( 1000);

    qDebug("Send file: %s %d\n",currentFileName.toLatin1().data(),_totalSize);
}
bool TcpFileSocket::GoOnSend(qint64 numBytes)  //开始发送文件内容
{
    qint64 realSendSize=qMin(numBytes, _byteToWrite);
    if(realSendSize>0)
    {
        _outBlock = _localFile->read(realSendSize);
        write(_outBlock);
        waitForBytesWritten(); //30second
        qDebug("send %d\n",100-((_byteToWrite*100)/_totalSize));
    }
    _byteToWrite -= realSendSize;  //剩余数据大小
    if(_byteToWrite<0)
        _byteToWrite=0;

    if(_byteToWrite == 0)  //发送完毕
    {
        qDebug("Send Completely\n");
        _localFile->close();
        return true;
    }
    else
    {
        return false;
    }
}
