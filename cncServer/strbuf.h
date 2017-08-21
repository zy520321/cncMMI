#ifndef STRBUF_H
#define STRBUF_H

#include <QThread>

class BufImpl;
class StrBuf : public QThread
{
    Q_OBJECT
public:
    explicit StrBuf(int bufCapacity,QObject *parent = 0);
    ~StrBuf();
    void InitBuf(unsigned int *got=NULL,unsigned int* received=NULL,unsigned int* capacity=NULL);
    bool GetBufStr(QString& getStr);
    bool IsCanGetBuf();

signals:
    void signalBufStateChg(int state);

public slots:
    void slotStrAccept(QString msg);
    void slotBufConnect(bool chg); // 1--connect 0--close

private:
    BufImpl* _buf;
};

#endif // STRBUF_H
