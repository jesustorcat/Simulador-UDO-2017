#include "simulador.h"
#include "ui_simulador.h"

simulador::simulador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulador)
{
    ui->setupUi(this);
}

simulador::~simulador()
{
    delete ui;
}
