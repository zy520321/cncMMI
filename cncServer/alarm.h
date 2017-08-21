#ifndef ALARM_H
#define ALARM_H

#include "strbuf.h"

#define  EMERGENCY  1

namespace SysAlarm
{
    class Alarm: public StrBuf
    {
        Q_OBJECT
    private:
        explicit Alarm(int capacity=50,QObject *parent = 0);
    public:
        ~Alarm();

        static Alarm* GetAlarmEngine();
        void InitData();

        void AddErr(int no,int line=-1, int prog=-1);
        bool GetErr(QString& err);
    };
}

#endif // ALARM_H
