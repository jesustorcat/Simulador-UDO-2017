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

namespace Ui {
class simulador_computador;
}

class simulador_computador : public QMainWindow
{
    Q_OBJECT

public:
    explicit simulador_computador(QWidget *parent = 0);
    ~simulador_computador();
    void ejecutar();

    //Señales de control
    int CA, LA, CB, LB, CF, LF, OP, CRI, LRI, EM, LM, CCP, LCP, ICP, DCP, CRDM, CE, LE, CS, RT;
    long _F, _indicadores;

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
