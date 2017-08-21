#ifndef TCPFILESOCKET_H
#define TCPFILESOCKET_H

#include "tcpclientsocket.h"
#include "strbuf.h"

// PROG
#define S_FILL_READ       "ReadFile"
#define E_FILL_READ       "FinishRead"
#define S_FILL_WRITE      "WriteFile"
#define S_FILL_WRITE_ACK  "CanWriteFile"
#define E_FILL_WRITE      "FinishWrite"

#define FILL_READ_TYPE         100
#define FILL_READ_NAME_TYPE    101
#define FILL_WRITE_TYPE        200


class TcpFileSocket : public TcpClientSocket
{
    Q_OBJECT

public:
    explicit TcpFileSocket( bool **connectedState=NULL, QObject *parent = NULL );
    ~TcpFileSocket();

signals:
    void    signalChgState(bool isConnect);
    void    signalSendFile(QString fileName);
    void    signalSendFileContent();

public slots:
    void    OnSendFile(QString fileName);
    void    OnGetFile(QString fileName);
protected:
    void ParseData( const char *data);

private slots:
    virtual void OnReadyRead();
    void    OnReadyReceiveFile();
    void    SendFileHead(QString fileName);  //传送文件头信息
    void    SendFileContent();  //start传送文件内容
    bool    GoOnSend(qint64 numBytes);  //传送文件内容

private:
    QString      _fileName;  //文件名
    qint64       _totalSize;  //总共文件大小（文件内容&文件名信息）
 //文件发送
    QFile *      _localFile;
    QByteArray   _outBlock;  //分次传
    qint64       _loadSize;  //每次发送数据的大小
    qint64       _byteToWrite;  //剩余数据大小
    bool         _needTerminateSend;
    int          _sendTimes;  //用来标记是否为第一次发送，第一次以后连接信号触发，后面的则手动调用
    bool         _startSendFlag;

 //文件 receive
    QFile *      _newFile;
    QByteArray   _inBlock;
    qint64       _byteReceived;  //已经发送的大小
};

#endif // TCPFILESOCKET_H
