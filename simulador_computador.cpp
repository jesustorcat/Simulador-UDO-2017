#include "simulador_computador.h"
#include "ui_simulador_computador.h"

simulador_computador::simulador_computador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulador_computador)
{
    ui->setupUi(this);
}

    //Temporizador, funcionará como el reloj del computador.
    long temp = 0, i= 0;
    long int memoria[255];

    //Objetos
    UNIDAD_ARITMETICO_LOGICA ual;
    UNIDAD_DE_CONTROL uc;

void simulador_computador::ejecutar(){

    //Las Señales de Control se inicializan en cero.
    CA = 0; LA = 0; CB = 0; LB = 0; CF = 0; LF = 0, OP = 0, CRI = 0, EM = 0, RT = 0;
    LM = 0; CCP = 0; LCP = 0; ICP = 0; DCP = 0; CRDM = 0; CE = 0; LE = 0; CS = 0; LRI = 0;

    temp = ui->reloj->text().toLong();

    uc.cargar_temporizador(temp);
    uc.cargar_ri(ui->reg_inst_1->text().toLong());

    //Cargar señales de control a la unidad de control
    uc.ejecutar_control(CA, LA, CB, LB, CF
                        ,LF, CRI, LRI, RT, CCP
                        ,LCP, ICP, DCP, EM, LM
                        ,CRDM, CE, LE, CS);

    //Carga el contenido del Registro de Contador de Programa hacia el bus
    if (LM == 1){
        ui->bus_principal->setText(ui->registro_cp->text());
    }
    else{

    }

    //Carga el contenido de la memoria al bus principal.
    if (LM == 1){
        i = ui->registro_dm->text().toLong();

        ui->bus_principal->setText(QString::number(memoria[i], 16).toUpper());
    }
    else{

    }

    //Carga el contenido del registro F hacia el bus principal.
    if (LF == 1){
        ui->bus_principal->setText(ui->reg_f_1->text());
    }
    else{

    }

    //Carga el contenido del puerto de entrada al bus principal.
    if (CE == 1){
        ui->bus_principal->setText(ui->puerto_entrada->text());
    }

    //Carga el contenido del bus principal al registro de contador de programa.
    if (CCP == 1){
        ui->registro_cp->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus en el registro de direccionamiento de memoria.
    if (CRDM == 1){
        ui->registro_dm->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus hacia el registro de instrucciones.
    if (CRI == 1){
        ui->reg_inst_1->setText(ui->bus_principal->text());
        uc.cargar_ri(ui->reg_inst_1->text().toLong());
    }
    else {

    }

    //Cargar el contenido del bus en el puerto de salida.
    if (CS == 1){
        ui->puerto_salida->setText(ui->bus_principal->text());
    }
    else {

    }

    //Cargar contenido del puerto de entrada
    if (CE == 1){
        ui->puerto_entrada->text().toLong();
    }

    //Cargar contenido del bus principal hacia el registro A.
    if (CA == 1){
        ui->reg_a_1->setText(ui->bus_principal->text());
        ual.cargar_a(ui->reg_a_1->text().toLong());
    }
    else {

    }

    //Cargar contenido del bus principal hacia el registro B.
    if (CB == 1){
        ui->reg_b_1->setText(ui->bus_principal->text());
        ual.cargar_b(ui->reg_b_1->text().toLong());
    }

    //Carga el código de operación de la unidad aritmético lógica.
    int op_1;
    op_1 = ui->op_1->text().toInt();
    ual.cargar_op(op_1);

    //Cargan funcion de la unidad aritmético lógica
    ual.operacion(F, indicadores);
}

simulador_computador::~simulador_computador()
{
    delete ui;
}

void simulador_computador::on_actionSalir_triggered()
{
    close();
}

void simulador_computador::on_actionPaso_triggered()
{
    QString reloj_hex = QString::number(temp, 16).toUpper();
    temp++;
    ui->reloj->setText(reloj_hex);

}

void simulador_computador::on_actionInstrucci_n_triggered()
{
    ejecutar();
}
