#include "simulador.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simulador w;
    w.show();

    return a.exec();
}
