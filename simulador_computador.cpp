#include "simulador_computador.h"
#include "ui_simulador_computador.h"

using namespace std;

long temp = 0, i = 0, reloj = 0;
long int memoria[255];

//Objetos
UNIDAD_ARITMETICO_LOGICA ual;
UNIDAD_DE_CONTROL uc;


simulador_computador::simulador_computador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulador_computador)
{
    ui->setupUi(this);
}

void simulador_computador::ejecutar(){

    //Las Señales de Control se inicializan en cero.
    CA = 0; LA = 0; CB = 0; LB = 0; CF = 0; LF = 0, OP = 0, CRI = 0, EM = 0, RT = 0;
    LM = 0; CCP = 0; LCP = 0; ICP = 0; DCP = 0; CRDM = 0; CE = 0; LE = 0; CS = 0; LRI = 0;

    ui->reg_temp_1->setText(QString::number(temp, 16).toUpper());

    uc.cargar_ri(ui->reg_inst_1->text().toLong());
    uc.cargar_temporizador(ui->reg_temp_1->text().toLong());

    //Cargar señales de control a la unidad de control
    uc.ejecutar_control(CA, LA, CB, LB, CF
                        ,LF, CRI, LRI, RT, CCP
                        ,LCP, ICP, DCP, EM, LM
                        ,CRDM, CE, LE, CS, OP);

    //Carga el contenido del Registro de Contador de Programa hacia el bus
    if (LCP == 1){
        ui->bus_principal->setText(ui->registro_cp->text());
    }
    else{

    }

    //Carga el contenido de la memoria al bus principal.
    if (LM == 1){
        i = ui->registro_dm->text().toLong();
        ui->memoria_principal_1->setText(QString::number(memoria[i], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_1->text());
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
    if (LE == 1){
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
    else {

    }

    //Carga el código de operación de la unidad aritmético lógica.
    int op_1;
    op_1 = ual.cargar_op(OP);
    ui->op_1->setText(QString::number(op_1, 16).toUpper());

    //Cargan funcion de la unidad aritmético lógica
    ual.operacion(_F, _indicadores);

    //Carga un registro en la memoria.
    if (EM == 1){

        i = ui->registro_dm->text().toLong();
        ui->memoria_principal_1->setText(QString::number(memoria[i], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_1->text());
        //memoria[i] = ui->memoria_principal_1->text().toLong();
    }
    else{

    }

    //Cargar contenido en el registro F.
    if (CF == 1){
        //ui->reg_f_1->setText();
    }
    else {

    }

    //Incrementar registro contador de programa.
    if (ICP == 1){
        long x;
        x = ui->registro_cp->text().toLong();
        x++;
        ui->registro_cp->setText(QString::number(x, 16).toUpper());
    }
    else {

    }

    //Decrementar registro contador de programa.
    if (DCP == 1){
        long x;
        x = ui->registro_cp->text().toLong();
        x--;
        ui->registro_cp->setText(QString::number(x, 16).toUpper());
    }

    //Reinicio del registro temporizador.
    if (RT == 1){
        ui->reg_temp_1->setText("0");
        temp = 0;
    }
    else {
        temp = ui->reg_temp_1->text().toLong();
        ++temp;
    }

    QString reloj_hex = QString::number(reloj, 16).toUpper();
    reloj++;
    ui->reloj->setText(reloj_hex);

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
    ejecutar();
}

void simulador_computador::on_actionInstrucci_n_triggered()
{
    int instruccion;
    ejecutar();

    do {
        ejecutar();
        instruccion = ui->reg_temp_1->text().toInt();
    } while (instruccion != 0);
}

void simulador_computador::on_actionReiniciar_triggered()
{
    ui->bus_principal->setText("0");
    ui->bus_secuandario_1->setText("0");
    ui->bus_secundario_2->setText("0");
    ui->bus_secundario_3->setText("0");
    ui->bus_secundario_4->setText("0");
    ui->memoria_principal_1->setText("0");
    ui->memoria_principal_2->setText("0");
    ui->memoria_principal_3->setText("0");
    ui->memoria_principal_4->setText("0");
    ui->registro_cp->setText("0");
    ui->registro_dm->setText("0");
    ui->puerto_salida->setText("0");
    ui->puerto_entrada->setText("");
    ui->reg_a_1->setText("0");
    ui->reg_a_2->setText("0");
    ui->reg_a_3->setText("0");
    ui->reg_a_4->setText("0");
    ui->reg_b_1->setText("0");
    ui->reg_b_2->setText("0");
    ui->reg_b_3->setText("0");
    ui->reg_b_4->setText("0");
    ui->reg_f_1->setText("0");
    ui->reg_f_2->setText("0");
    ui->reg_f_3->setText("0");
    ui->reg_f_4->setText("0");
    ui->reg_temp_1->setText("0");
    ui->reg_temp_2->setText("0");
    ui->reg_temp_3->setText("0");
    ui->reg_temp_4->setText("0");
    ui->reg_inst_1->setText("0");
    ui->reg_inst_2->setText("0");
    ui->reg_inst_3->setText("0");
    ui->reg_inst_4->setText("0");
    ui->op_1->setText("");
    ui->op_2->setText("");
    ui->op_3->setText("");
    ui->op_4->setText("");
    ui->reloj->setText("");

    i = 0;

    for (int j = 0; j < 255; j++)
        memoria[j] = 0;

    reloj = 0;
    temp = 0;

}

void simulador_computador::on_actionSimular_triggered()
{
    char xy[10];
    long i;
    long int valor;

    ifstream archivo_objeto("codigo_objeto.dat");

    archivo_objeto.getline(xy,10);
    i = atol(xy);

    while (!archivo_objeto.eof()){
        archivo_objeto.getline(xy,10);
        valor = strtol(xy,NULL,0);
        memoria[i] = valor;
        i++;
        cout << valor << endl;
    }

    archivo_objeto.close();
}
