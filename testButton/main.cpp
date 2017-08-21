#include "widget.h"
#include <QApplication>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QFile file("/home/sibonac/workspace/skin/button.qss");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = file.readAll();
        a.setStyleSheet(qss);
        file.close();
    }

    return a.exec();
}
