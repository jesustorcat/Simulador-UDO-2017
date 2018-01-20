#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

namespace Ui {
class simulador;
}

class simulador : public QMainWindow
{
    Q_OBJECT

public:
    explicit simulador(QWidget *parent = 0);
    ~simulador();

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

private:
    Ui::simulador *ui;
    QString archivo_txt;
};

#endif // SIMULADOR_H
