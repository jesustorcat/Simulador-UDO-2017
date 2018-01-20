#include "simulador.h"
#include <QApplication>
#include <unidad_aritmetico_logica.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simulador w;
    w.show();

    return a.exec();
}
