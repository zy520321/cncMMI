#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QThread>

namespace InterpCtrl
{
    class Pimpl;
    class Interpolation : public QThread
    {
        Q_OBJECT
    public:
        explicit Interpolation(unsigned int goupNo,QObject *parent = 0);
        ~Interpolation();
        bool InitLoadDLL(char* path);
        void Stop();

    public:
        unsigned int _GroupNo;

    protected:
        void run();

    signals:

    public slots:

    private:
        Pimpl* data;
    };
}

#endif // INTERPOLATION_H
