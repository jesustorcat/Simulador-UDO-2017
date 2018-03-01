#ifndef SIMULADOR_COMPUTADOR_H
#define SIMULADOR_COMPUTADOR_H

#include <QMainWindow>

namespace Ui {
class simulador_computador;
}

class simulador_computador : public QMainWindow
{
    Q_OBJECT

public:
    explicit simulador_computador(QWidget *parent = 0);
    ~simulador_computador();

private:
    Ui::simulador_computador *ui;
};

#endif // SIMULADOR_COMPUTADOR_H
