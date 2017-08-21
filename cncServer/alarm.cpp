#include "alarm.h"

namespace SysAlarm
{
    class AlarmData
    {
      int _errNo;
      int _errLine;
      int _errProg;
      bool _stopInterp;
      bool _stopControl;
public:
      QString msg_str;

      AlarmData(int no)
      {
          _errNo=no;
          _errLine=-1;
          _errProg=-1;
          _stopInterp=true;
          _stopControl=true;

          msg_str = "err as: " + QString::number(_errNo);
      }
      AlarmData(int no,int line, int prog)
      {
          _errNo=no;
          _errLine=line;
          _errProg=prog;
          _stopInterp=true;
          _stopControl=true;

          msg_str = "err as: " + QString::number(_errNo) + "row " + QString::number(_errLine) + "file" + QString::number(_errProg);
      }
    };


    Alarm::Alarm(int capacity,QObject *parent) :
        StrBuf(capacity,parent)
    {
    }
    Alarm::~Alarm()
    {

    }
    Alarm* Alarm::GetAlarmEngine()
    {
        static Alarm* theEngine=NULL;
        if(NULL==theEngine)
        {
            theEngine=new Alarm(100);
        }
        return theEngine;
    }
    void Alarm::InitData()
    {
        InitBuf();
        //
    }

    void Alarm::AddErr(int no,int line, int prog)
    {
        AlarmData curErr(no,line,prog);
        slotStrAccept(curErr.msg_str);
    }
    bool Alarm::GetErr(QString& err)
    {
        return GetBufStr(err);
    }
}
