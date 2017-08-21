#include "serverthreadctrl.h"

ServerThreadCtrl::ServerThreadCtrl()
{
    _runningNum=0;

    _thMsgLoopLaser = new QThread();
    _thMsgLoopProg = new QThread();
    _thMsgLoopCmd = new QThread();

    _serverLaser = new ServerSocket(false,5000);
    _serverCmd = new ServerSocket(false,6000);
    _serverProg = new ServerSocket(true,7000);

    _serverLaser->moveToThread(_thMsgLoopLaser);
    _serverCmd->moveToThread(_thMsgLoopCmd);
    _serverProg->moveToThread(_thMsgLoopProg);

    _thMsgLoopLaser->start();
    _thMsgLoopProg->start();
    _thMsgLoopCmd->start();
}

ServerThreadCtrl::~ServerThreadCtrl()
{
    _serverLaser->close();
    _serverCmd->close();
    _serverProg->close();

    delete _serverLaser;
    delete _serverCmd;
    delete _serverProg;

    delete _thMsgLoopLaser;
    delete _thMsgLoopCmd;
    delete _thMsgLoopProg;
}

void ServerThreadCtrl::run()
{
#if _DEBUG_==1
    TerminalTest();
#else
 #endif
}

void ServerThreadCtrl::startLoop(int seleType)
{
    if((ServerThreadNum==seleType||0==seleType)
      &&!_thMsgLoopCmd->isRunning())
    {
        _thMsgLoopCmd->start();
        _runningNum++;
    }
    if((ServerThreadNum==seleType||1==seleType)
      &&!_thMsgLoopProg->isRunning())
    {
        _thMsgLoopProg->start();
        _runningNum++;
    }
    if((ServerThreadNum==seleType||2==seleType)
      &&!_thMsgLoopLaser->isRunning())
    {
        _thMsgLoopLaser->start();
        _runningNum++;
    }
    start();
}

void ServerThreadCtrl::terminateLoop(int seleType)
{
    if((ServerThreadNum==seleType||seleType==0)
      &&_thMsgLoopCmd->isRunning())
    {
         _thMsgLoopCmd->terminate();
         _runningNum--;
    }
    if((ServerThreadNum==seleType||seleType==1)
      &&_thMsgLoopProg->isRunning())
    {
         _thMsgLoopProg->terminate();
         _runningNum--;
    }
    if((ServerThreadNum==seleType||seleType==2)
      &&_thMsgLoopLaser->isRunning())
    {
         _thMsgLoopLaser->terminate();
         _runningNum--;
    }
}

void ServerThreadCtrl::setCallBack(transterData callback, void * pVoid)
{
    if (_serverCmd)
    {
        _serverCmd->setCallBack(callback, pVoid);
    }
}

void ServerThreadCtrl::TerminalTest()
{
    char testSendBuf[256];
    while(0<_runningNum)
    {
        gets(testSendBuf);
        if(strcmp(testSendBuf,"out")==0)
            break;
        if(_thMsgLoopCmd->isRunning())
            _serverCmd->updateClients(testSendBuf,strlen(testSendBuf)+1);
        if(_thMsgLoopProg->isRunning())
            _serverProg->updateClients(testSendBuf,strlen(testSendBuf)+1);
        if(_thMsgLoopLaser->isRunning())
            _serverLaser->updateClients(testSendBuf,strlen(testSendBuf)+1);
        memset(testSendBuf,0,sizeof(testSendBuf));
    }
}
