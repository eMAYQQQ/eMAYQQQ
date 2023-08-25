#include "tcpserverwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tcpServerWidget w;
    w.show();
    return a.exec();
}
