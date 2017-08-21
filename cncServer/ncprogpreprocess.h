#ifndef NCPROGPREPROCESS_H
#define NCPROGPREPROCESS_H

#include "strbuf.h"

class NcProgProcess : public StrBuf
{
    Q_OBJECT
private:
    explicit NcProgProcess(int capacity=50,QObject *parent = 0);
public:
    ~NcProgProcess();

    static NcProgProcess* GetNcEngine();
    void InitData(unsigned int ctrl);

protected:
    void run();

signals:

public slots:
private:
    unsigned char _ctrlType;
};

#endif // NCPROGPREPROCESS_H
