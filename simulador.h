#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include "analizador_lexico.h"
#include "analizador_sintactico.h"
#include "simulador_computador.h"

namespace Ui {
class simulador;
}

class simulador : public QMainWindow
{
    Q_OBJECT

public:
    explicit simulador(QWidget *parent = 0);
    ~simulador();
    simulador_computador *ventana_simulador = NULL;

private slots:
    void on_actionNuevo_triggered();

    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

    void on_actionGuardar_como_triggered();

    void on_actionDeshacer_triggered();

    void on_actionRehacer_triggered();

    void on_actionCortar_triggered();

    void on_actionCopiar_triggered();

    void on_actionPegar_triggered();

    void on_actionAcerca_de_triggered();

    void on_actionSalir_triggered();

    void on_actionCompilar_triggered();

    void on_actionEjecutar_triggered();

    void on_actioncancelar_triggered();

private:
    Ui::simulador *ui;
    QString archivo_txt;
    int *h;
};

#endif // SIMULADOR_H
