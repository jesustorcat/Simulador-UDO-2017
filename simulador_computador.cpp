#include "simulador_computador.h"
#include "ui_simulador_computador.h"

simulador_computador::simulador_computador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulador_computador)
{
    ui->setupUi(this);
}

simulador_computador::~simulador_computador()
{
    delete ui;
}
