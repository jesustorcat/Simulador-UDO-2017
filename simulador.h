#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QMainWindow>

namespace Ui {
class simulador;
}

class simulador : public QMainWindow
{
    Q_OBJECT

public:
    explicit simulador(QWidget *parent = 0);
    ~simulador();

private:
    Ui::simulador *ui;
};

#endif // SIMULADOR_H
