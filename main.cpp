#include "GoBang.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GoBang w;
    w.show();
    return a.exec();
}
