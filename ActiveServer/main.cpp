#include "ActiveServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ActiveServer w;
    w.show();
    return a.exec();
}
