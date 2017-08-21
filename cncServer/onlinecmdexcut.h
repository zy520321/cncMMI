#ifndef ONLINECMDEXCUT_H
#define ONLINECMDEXCUT_H

#include <QThread>
#include "protocol/analyzeEncapsulate.h"

namespace WorkModel
{
    class Ipmpl;

    class OnLineCmdExcut : public QThread
    {
        Q_OBJECT
    private:
        explicit OnLineCmdExcut();
    public:
        ~OnLineCmdExcut();
        static OnLineCmdExcut* GetCmdExcut();
        void Init();
        static int transData(ADDR_INFO * addrInfo, int counts, void * pVoid);

    protected:
        void run();

    signals:

    public slots:

    private:
        Ipmpl *data;
    };
}

#endif // ONLINECMDEXCUT_H
