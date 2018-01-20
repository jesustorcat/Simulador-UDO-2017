#include "acerca_de.h"
#include "ui_acerca_de.h"

acerca_de::acerca_de(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::acerca_de)
{
    ui->setupUi(this);
}

acerca_de::~acerca_de()
{
    delete ui;
}
