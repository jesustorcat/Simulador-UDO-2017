#include "simulador.h"
#include "ui_simulador.h"

simulador::simulador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulador)
{
    ui->setupUi(this);
    setWindowTitle("Simulador UDO-2017");
    setCentralWidget(ui->textEdit);
}

simulador::~simulador()
{
    delete ui;
}

void simulador::on_actionNuevo_triggered()
{
    ui->textEdit->setPlainText("");
}

void simulador::on_actionAbrir_triggered()
{

}

void simulador::on_actionGuardar_triggered()
{

}

void simulador::on_actionGuardar_como_triggered()
{

}

void simulador::on_actionDeshacer_triggered()
{
    ui->textEdit->undo();
}

void simulador::on_actionRehacer_triggered()
{
    ui->textEdit->redo();
}

void simulador::on_actionCortar_triggered()
{
    ui->textEdit->cut();
}

void simulador::on_actionCopiar_triggered()
{
    ui->textEdit->copy();
}

void simulador::on_actionPegar_triggered()
{
    ui->textEdit->paste();
}

void simulador::on_actionAcerca_de_triggered()
{
    QString about_txt;
    about_txt = "Autor: Jesús Briceño\n";
    about_txt += "Fecha: Febrero 2018\n";
    about_txt += "Versión: 1.0.2";
    QMessageBox::about(this,"Simulador UDO-2017", about_txt);
}

void simulador::on_actionSalir_triggered()
{
    close();
}
