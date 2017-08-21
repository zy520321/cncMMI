#include "strbuf.h"
#include <vector>

class BufImpl
{
public:
    BufImpl(int bufCapacity=999999);
    ~BufImpl();
    void Init();

public:
    unsigned int _state;  //0--init 1--ready 2--full  3--busy
    std::vector<QString> _bufList;
    int _capacity;
    int _fillNo;
    int _getNo;
    int _realBufNum;
    int _getBufNum;
    bool _canInteractive;

    unsigned int* _FGot;
    unsigned int* _FReceived;
};
BufImpl::BufImpl(int bufCapacity)
{
    _canInteractive=false;
    _capacity=bufCapacity;
    QString emptyStr("");
    for(int i=0; i<_capacity; i++)
    {
        _bufList.push_back(emptyStr);
    }
}
BufImpl::~BufImpl()
{
}
void BufImpl::Init()
{
    _fillNo=0;
    _getNo=0;
    _state=0;
    _realBufNum=0;
    _getBufNum=0;
    QString emptyStr("");
    for(int i=0; i<_capacity; i++)
    {
        _bufList.at(i)=emptyStr;
    }
}

StrBuf::StrBuf(int bufCapacity,QObject *parent) :
    QThread(parent)
{
    _buf= new BufImpl(bufCapacity);
}
StrBuf::~StrBuf()
{
    delete _buf;
}
void StrBuf::InitBuf(unsigned int *got,unsigned int* received,unsigned int* capacity)
{
    _buf->Init();
    //emit signalBufStateChg(0);
    _buf->_canInteractive=true;

    if(got!=NULL)
    {
        _buf->_FGot=got;
        *_buf->_FGot=0;
    }

    if(received!=NULL)
    {
        _buf->_FReceived=received;
        *_buf->_FReceived=0;
    }

    if(capacity!=NULL)
        *capacity=_buf->_capacity;
}
bool StrBuf::IsCanGetBuf()
{
    return _buf->_canInteractive;
}
bool StrBuf::GetBufStr(QString& getStr)
{
    if(_buf->_getBufNum<_buf->_realBufNum)
    {
        getStr=_buf->_bufList.at(_buf->_getNo);
        _buf->_getNo = (_buf->_getNo+1) % _buf->_capacity;
        _buf->_getBufNum++;
        if(*_buf->_FGot)
            *_buf->_FGot++;

        if(_buf->_state==2)
            _buf->_state=1;
        else if(_buf->_getBufNum>=_buf->_realBufNum)
            _buf->_state=0;
        return true;
    }
    _buf->_state=0;
    return false;
}
void StrBuf::slotStrAccept(QString msg)
{
    if(!_buf->_canInteractive||_buf->_state>1)
        return;

    _buf->_bufList.at(_buf->_fillNo)=msg;
    _buf->_fillNo = (_buf->_fillNo+1) % _buf->_capacity;
    _buf->_realBufNum++;
    if(*_buf->_FReceived)
        *_buf->_FReceived++;

    if(_buf->_realBufNum>=(_buf->_getBufNum+_buf->_capacity))
    {
        _buf->_state=2;
        emit signalBufStateChg(2);
    }
    else if(_buf->_state!=1&&_buf->_realBufNum>_buf->_getBufNum)
    {
        _buf->_state=1;
        emit signalBufStateChg(1);
    }
}
void StrBuf::slotBufConnect(bool chg)
{
    if(chg)
    {
        InitBuf();
    }
    _buf->_canInteractive=chg;
}
