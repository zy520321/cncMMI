#include "ncprogpreprocess.h"
#include "DefSysSignalAndData.h"
#include "interpsegdata.h"

NcProgProcess::NcProgProcess(int capacity,QObject *parent) :
    StrBuf(capacity,parent)
{
    _ctrlType=1;
}
NcProgProcess::~NcProgProcess()
{

}
NcProgProcess* NcProgProcess::GetNcEngine()
{
    static NcProgProcess* theEngine=NULL;
    if(NULL==theEngine)
    {
        I_ROT_BUF_STATE_SYS(1);
        unsigned int capacity = ReadI_NCPROG_ROTBUF;
        if(capacity<200)
        {
            capacity=200;
        }
        else if(capacity>10000)
        {
            capacity=10000;
        }
        I_NCPROG_ROTBUF(capacity);
        theEngine=new NcProgProcess(capacity);
    }
    return theEngine;
}
void NcProgProcess::InitData(unsigned int ctrl)
{
    if(1!=ctrl)
    {
        _ctrlType=ctrl;
        if(_ctrlType==0&&IsCanGetBuf())
            slotBufConnect(false);
        return;
    }
    int count=100;
    while(isRunning())
    {
        slotBufConnect(false);
        if(--count>0)
            msleep(10);
        else
            break;
        terminate();
    }
    if(isRunning())
        terminate();

    InitInterpSegBuf();
    InitBuf(ReadI_RECEIVED_SEG_COUNT_SYS,ReadI_GOT_SEG_COUNT_SYS,ReadI_CAPACITY_SEG_SYS);

    start();
}
void NcProgProcess::run()
{
    QString curSegStr;
    InterpSegData segData;

    while(IsCanGetBuf())
    {
        if(2==_ctrlType)
        {
            InitInterpSegBuf();
            InitBuf();
            _ctrlType=1;
        }
        if(ReadFM_OP&&!IsInterpSegBufFull()&&GetBufStr(curSegStr))
        {
            ParseNcSeg(curSegStr,segData);
            FillInterpSegDataBuf(&segData);
        }
        I_ROT_BUF_FULL_SYS(((ReadI_RECEIVED_SEG_COUNT_SYS-ReadI_ROT_BUF_STATE_SYS)==ReadI_CAPACITY_SEG_SYS) ? 1 : 0);
        msleep(20);
    }
    ChangeInterpSegBufState(false);
}

