#ifndef SIMULADOR_COMPUTADOR_H
#define SIMULADOR_COMPUTADOR_H

#include <QMainWindow>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <QDebug>
#include "unidad_aritmetico_logica.h"
#include "unidad_de_control.h"
#include "arbitro_de_bus.h"

namespace Ui {
class simulador_computador;
}

class simulador_computador : public QMainWindow
{
    Q_OBJECT

public:
    explicit simulador_computador(QWidget *parent = 0);
    ~simulador_computador();
    void proxima_instruccion_n1();
    void cargar_codigo_n1();
    void cargar_codigo_n2();
    void cargar_codigo_n3();
    void cargar_codigo_n4();
    void ejecutar_n1();
    void ejecutar_n2();
    void ejecutar_n3();
    void ejecutar_n4();
    void ejecutar_pulsos();
    void asignar_nucleo(int&);
    void copiar_regitros_n1();
    void copiar_regitros_n2();
    void copiar_regitros_n3();
    void copiar_regitros_n4();
    long incrementar(long);
    long decrementar(long);

    //Señales de control
    int CA, LA, CB, LB, CF, LF, OP, CRI, LRI, EM, LM, CCP, LCP, ICP, DCP, CRDM, CE, LE, CS, RT;
    long _F, _indicadores;

    //Señales del árbitro de bus.
    int nucleo;
    bool X1, X2, X3, X4;

private slots:
    void on_actionSalir_triggered();

    void on_actionPaso_triggered();

    void on_actionInstrucci_n_triggered();

    void on_actionReiniciar_triggered();

    void on_actionSimular_triggered();

private:
    Ui::simulador_computador *ui;
};

#endif // SIMULADOR_COMPUTADOR_H
