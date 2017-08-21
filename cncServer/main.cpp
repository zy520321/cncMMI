#include <QCoreApplication>
#include "onlinecmdexcut.h"
#include <QThread>

QCoreApplication *thisApp;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    thisApp=&a;

    qDebug("main thread id=%x....\n", QThread::currentThreadId());

    WorkModel::OnLineCmdExcut::GetCmdExcut()->Init();

    return a.exec();
}
