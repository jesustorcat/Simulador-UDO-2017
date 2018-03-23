#include "simulador_computador.h"
#include "ui_simulador_computador.h"

using namespace std;

long temp = 0, i = 0, registro_cp1 = 0, registro_dm1 = 0, reloj = 0; //Núcleo 1 y reloj.
long temp_2 = 0, i2 = 0, registro_cp2 = 0, registro_dm2 = 0;  //Núcleo 2.
long temp_3 = 0, i3 = 0, registro_cp3 = 0, registro_dm3 = 0;  //Núcleo 3.
long temp_4 = 0, i4 = 0, registro_cp4 = 0, registro_dm4 = 0;  //Núcleo 4.
long int memoria[255];
long int memoria_n2[255];
long int memoria_n3[255];
long int memoria_n4[255];
bool ok;

int turno = 0;

//Objetos
UNIDAD_ARITMETICO_LOGICA ual_1, ual_2, ual_3, ual_4;
UNIDAD_DE_CONTROL uc_1, uc_2, uc_3, uc_4;
ARBITRO_DE_BUS ab;


simulador_computador::simulador_computador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulador_computador)
{
    ui->setupUi(this);
}

void simulador_computador::ejecutar_n1(){

    CA = 0; LA = 0; CB = 0; LB = 0; CF = 0; LF = 0, OP = 0, CRI = 0, EM = 0, RT = 0;
    LM = 0; CCP = 0; LCP = 0; ICP = 0; DCP = 0; CRDM = 0; CE = 0; LE = 0; CS = 0; LRI = 0;

    ui->reg_temp_1->setText(QString::number(temp, 16).toUpper());

    uc_1.cargar_ri(ui->reg_inst_1->text().toLong(&ok, 16));
    uc_1.cargar_temporizador(ui->reg_temp_1->text().toLong());

    //Cargar señales de control a la unidad de control
    uc_1.ejecutar_control(CA, LA, CB, LB, CF
                        ,LF, CRI, LRI, RT, CCP
                        ,LCP, ICP, DCP, EM, LM
                        ,CRDM, CE, LE, CS, OP);

    //Carga el contenido del Registro de Contador de Programa hacia el bus
    if (LCP == 1){
        ui->bus_principal->setText(ui->registro_cp->text());
        ui->bus_secuandario_1->setText(ui->bus_principal->text());
    }
    else{

    }

    //Carga el contenido de la memoria al bus principal.
    if (LM == 1){
        i = ui->registro_dm->text().toLong(&ok, 16);
        ui->memoria_principal_1->setText(QString::number(memoria[i], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_1->text());
        ui->bus_secuandario_1->setText(ui->bus_principal->text());

        cout << i << endl;
    }
    else{

    }

    //Carga el contenido del registro F hacia el bus principal.
    if (LF == 1){
        ui->bus_secuandario_1->setText(ui->reg_f_1->text());
    }
    else{

    }

    //Carga el contenido del puerto de entrada al bus principal.
    if (LE == 1){
        ui->bus_principal->setText(ui->puerto_entrada->text().toUpper());
        ui->bus_secuandario_1->setText(ui->bus_principal->text());
    }

    //Carga el contenido del bus principal al registro de contador de programa.
    if (CCP == 1){
        //ui->bus_principal->setText(ui->bus_secuandario_1->text());
        ui->registro_cp->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus en el registro de direccionamiento de memoria.
    if (CRDM == 1){
        //ui->bus_principal->setText(ui->bus_secuandario_1->text());
        ui->registro_dm->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus hacia el registro de instrucciones.
    if (CRI == 1){
        ui->bus_secuandario_1->setText(ui->bus_principal->text());
        ui->reg_inst_1->setText(ui->bus_secuandario_1->text());
        uc_1.cargar_ri(ui->reg_inst_1->text().toLong(&ok, 16));
    }
    else {

    }

    //Cargar el contenido del bus en el puerto de salida.
    if (CS == 1){
        ui->bus_principal->setText(ui->bus_secuandario_1->text());
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
        ui->reg_a_1->setText(ui->bus_secuandario_1->text());
        ual_1.cargar_a(ui->reg_a_1->text().toLong(&ok, 16));
    }
    else {

    }

    //Cargar contenido del bus principal hacia el registro B.
    if (CB == 1){
        ui->reg_b_1->setText(ui->bus_secuandario_1->text());
        ual_1.cargar_b(ui->reg_b_1->text().toLong(&ok, 16));
    }
    else {

    }

    //Carga el código de operación de la unidad aritmético lógica.
    //ual.cargar_op(OP);
    ui->op_1->setText(QString::number(ual_1.cargar_op(OP), 10).toUpper());

    //Cargan funcion de la unidad aritmético lógica
    ual_1.operacion(_F, _indicadores);

    //Carga un registro en la memoria.
    if (EM == 1){

        i = ui->registro_dm->text().toLong();
        ui->memoria_principal_1->setText(QString::number(memoria[i], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_1->text());
        ui->bus_secuandario_1->setText(ui->bus_principal->text());
        //memoria[i] = ui->memoria_principal_1->text().toLong();
    }
    else{

    }

    //Cargar contenido en el registro F.
    if (CF == 1){
        ui->op_1->setText(QString::number(ual_1.cargar_op(OP), 10).toUpper());
        ual_1.operacion(_F, _indicadores);
        ui->reg_f_1->setText(QString::number(_F, 16).toUpper());
        //cout << OP << endl;
    }
    else {

    }

    //Incrementar registro contador de programa.
    if (ICP == 1){
        ui->registro_cp->setText(QString::number(incrementar(ui->registro_cp->text().toLong(&ok, 16)), 16).toUpper());
    }
    else {

    }

    //Decrementar registro contador de programa.
    if (DCP == 1){
        ui->registro_cp->setText(QString::number(decrementar(ui->registro_cp->text().toLong(&ok, 16)), 16).toUpper());
    }
    else {

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

}

void simulador_computador::ejecutar_n2(){

    CA = 0; LA = 0; CB = 0; LB = 0; CF = 0; LF = 0, OP = 0, CRI = 0, EM = 0, RT = 0;
    LM = 0; CCP = 0; LCP = 0; ICP = 0; DCP = 0; CRDM = 0; CE = 0; LE = 0; CS = 0; LRI = 0;

    ui->reg_temp_2->setText(QString::number(temp_2, 16).toUpper());

    uc_2.cargar_ri(ui->reg_inst_2->text().toLong(&ok, 16));
    uc_2.cargar_temporizador(ui->reg_temp_2->text().toLong());

    //Cargar señales de control a la unidad de control
    uc_2.ejecutar_control(CA, LA, CB, LB, CF
                        ,LF, CRI, LRI, RT, CCP
                        ,LCP, ICP, DCP, EM, LM
                        ,CRDM, CE, LE, CS, OP);

    //Carga el contenido del Registro de Contador de Programa hacia el bus
    if (LCP == 1){
        ui->bus_principal->setText(ui->registro_cp->text());
        ui->bus_secundario_2->setText(ui->bus_principal->text());
    }
    else{

    }

    //Carga el contenido de la memoria al bus principal.
    if (LM == 1){
        i2 = ui->registro_dm->text().toLong(&ok, 16);
        ui->memoria_principal_2->setText(QString::number(memoria_n2[i2], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_2->text());
        ui->bus_secundario_2->setText(ui->bus_principal->text());
    }
    else{

    }

    //Carga el contenido del registro F hacia el bus principal.
    if (LF == 1){
        ui->bus_secundario_2->setText(ui->reg_f_2->text());
    }
    else{

    }

    //Carga el contenido del puerto de entrada al bus principal.
    if (LE == 1){
        ui->bus_principal->setText(ui->puerto_entrada->text().toUpper());
        ui->bus_secundario_2->setText(ui->bus_principal->text());
    }

    //Carga el contenido del bus principal al registro de contador de programa.
    if (CCP == 1){
        //ui->bus_principal->setText(ui->bus_secundario_2->text());
        ui->registro_cp->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus en el registro de direccionamiento de memoria.
    if (CRDM == 1){
        ui->registro_dm->setText(ui->bus_secundario_2->text());
    }
    else {

    }

    //Carga el contenido del bus hacia el registro de instrucciones.
    if (CRI == 1){
        ui->bus_secundario_2->setText(ui->bus_principal->text());
        ui->reg_inst_2->setText(ui->bus_secundario_2->text());
        uc_2.cargar_ri(ui->reg_inst_2->text().toLong(&ok, 16));
    }
    else {

    }

    //Cargar el contenido del bus en el puerto de salida.
    if (CS == 1){
        ui->bus_principal->setText(ui->bus_secundario_2->text());
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
        ui->reg_a_2->setText(ui->bus_secundario_2->text());
        ual_2.cargar_a(ui->reg_a_2->text().toLong(&ok, 16));
    }
    else {

    }

    //Cargar contenido del bus principal hacia el registro B.
    if (CB == 1){
        ui->reg_b_2->setText(ui->bus_secundario_2->text());
        ual_2.cargar_b(ui->reg_b_2->text().toLong(&ok, 16));
    }
    else {

    }

    //Carga el código de operación de la unidad aritmético lógica.
    //ual.cargar_op(OP);
    ui->op_2->setText(QString::number(ual_2.cargar_op(OP), 10).toUpper());

    //Cargan funcion de la unidad aritmético lógica
    ual_2.operacion(_F, _indicadores);

    //Carga un registro en la memoria.
    if (EM == 1){

        i2 = ui->registro_dm->text().toLong();
        ui->memoria_principal_2->setText(QString::number(memoria_n2[i2], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_2->text());
        ui->bus_secundario_2->setText(ui->bus_principal->text());
        //memoria[i] = ui->memoria_principal_1->text().toLong();
    }
    else{

    }

    //Cargar contenido en el registro F.
    if (CF == 1){
        ui->op_2->setText(QString::number(ual_2.cargar_op(OP), 10).toUpper());
        ual_2.operacion(_F, _indicadores);
        ui->reg_f_2->setText(QString::number(_F, 16).toUpper());
        //cout << OP << endl;
    }
    else {

    }

    //Incrementar registro contador de programa.
    if (ICP == 1){
        ui->registro_cp->setText(QString::number(incrementar(ui->registro_cp->text().toLong(&ok, 16)), 16).toUpper());
    }
    else {

    }

    //Decrementar registro contador de programa.
    if (DCP == 1){
        ui->registro_cp->setText(QString::number(decrementar(ui->registro_cp->text().toLong(&ok, 16)), 16).toUpper());
    }
    else {

    }

    //Reinicio del registro temporizador.
    if (RT == 1){
        ui->reg_temp_2->setText("0");
        temp_2 = 0;
    }
    else {
        temp_2 = ui->reg_temp_2->text().toLong();
        ++temp_2;
    }
}

void simulador_computador::ejecutar_n3(){

    CA = 0; LA = 0; CB = 0; LB = 0; CF = 0; LF = 0, OP = 0, CRI = 0, EM = 0, RT = 0;
    LM = 0; CCP = 0; LCP = 0; ICP = 0; DCP = 0; CRDM = 0; CE = 0; LE = 0; CS = 0; LRI = 0;

    ui->reg_temp_3->setText(QString::number(temp_3, 16).toUpper());

    uc_3.cargar_ri(ui->reg_inst_3->text().toLong(&ok, 16));
    uc_3.cargar_temporizador(ui->reg_temp_3->text().toLong());

    //Cargar señales de control a la unidad de control
    uc_3.ejecutar_control(CA, LA, CB, LB, CF
                        ,LF, CRI, LRI, RT, CCP
                        ,LCP, ICP, DCP, EM, LM
                        ,CRDM, CE, LE, CS, OP);

    //Carga el contenido del Registro de Contador de Programa hacia el bus
    if (LCP == 1){
        ui->bus_principal->setText(ui->registro_cp->text());
        ui->bus_secundario_3->setText(ui->bus_principal->text());
    }
    else{

    }

    //Carga el contenido de la memoria al bus principal.
    if (LM == 1){
        i3 = ui->registro_dm->text().toLong(&ok, 16);
        ui->memoria_principal_3->setText(QString::number(memoria_n3[i3], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_3->text());
        ui->bus_secundario_3->setText(ui->bus_principal->text());
    }
    else{

    }

    //Carga el contenido del registro F hacia el bus principal.
    if (LF == 1){
        ui->bus_secundario_3->setText(ui->reg_f_3->text());
    }
    else{

    }

    //Carga el contenido del puerto de entrada al bus principal.
    if (LE == 1){
        ui->bus_principal->setText(ui->puerto_entrada->text().toUpper());
        ui->bus_secundario_3->setText(ui->bus_principal->text());
    }

    //Carga el contenido del bus principal al registro de contador de programa.
    if (CCP == 1){
        //ui->bus_principal->setText(ui->bus_secundario_3->text());
        ui->registro_cp->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus en el registro de direccionamiento de memoria.
    if (CRDM == 1){
        //ui->bus_principal->setText(ui->bus_secundario_3->text());
        ui->registro_dm->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus hacia el registro de instrucciones.
    if (CRI == 1){
        ui->bus_secundario_3->setText(ui->bus_principal->text());
        ui->reg_inst_3->setText(ui->bus_secundario_3->text());
        uc_3.cargar_ri(ui->reg_inst_3->text().toLong(&ok, 16));
    }
    else {

    }

    //Cargar el contenido del bus en el puerto de salida.
    if (CS == 1){
        ui->bus_principal->setText(ui->bus_secundario_3->text());
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
        ui->reg_a_3->setText(ui->bus_secundario_3->text());
        ual_3.cargar_a(ui->reg_a_3->text().toLong(&ok, 16));
    }
    else {

    }

    //Cargar contenido del bus principal hacia el registro B.
    if (CB == 1){
        ui->reg_b_3->setText(ui->bus_secundario_3->text());
        ual_3.cargar_b(ui->reg_b_3->text().toLong(&ok, 16));
    }
    else {

    }

    //Carga el código de operación de la unidad aritmético lógica.
    //ual.cargar_op(OP);
    ui->op_3->setText(QString::number(ual_3.cargar_op(OP), 10).toUpper());

    //Cargan funcion de la unidad aritmético lógica
    ual_3.operacion(_F, _indicadores);

    //Carga un registro en la memoria.
    if (EM == 1){

        i3 = ui->registro_dm->text().toLong();
        ui->memoria_principal_3->setText(QString::number(memoria_n3[i3], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_3->text());
        ui->bus_secundario_3->setText(ui->bus_principal->text());
        //memoria[i] = ui->memoria_principal_1->text().toLong();
    }
    else{

    }

    //Cargar contenido en el registro F.
    if (CF == 1){
        ui->op_3->setText(QString::number(ual_3.cargar_op(OP), 10).toUpper());
        ual_3.operacion(_F, _indicadores);
        ui->reg_f_3->setText(QString::number(_F, 16).toUpper());
    }
    else {

    }

    //Incrementar registro contador de programa.
    if (ICP == 1){
        ui->registro_cp->setText(QString::number(incrementar(ui->registro_cp->text().toLong(&ok, 16)), 16).toUpper());
    }
    else {

    }

    //Decrementar registro contador de programa.
    if (DCP == 1){
        ui->registro_cp->setText(QString::number(decrementar(ui->registro_cp->text().toLong(&ok, 16)), 16).toUpper());
    }
    else {

    }

    //Reinicio del registro temporizador.
    if (RT == 1){
        ui->reg_temp_3->setText("0");
        temp_3 = 0;
    }
    else {
        temp_3 = ui->reg_temp_3->text().toLong();
        ++temp_3;
    }
}

void simulador_computador::ejecutar_n4(){

    CA = 0; LA = 0; CB = 0; LB = 0; CF = 0; LF = 0, OP = 0, CRI = 0, EM = 0, RT = 0;
    LM = 0; CCP = 0; LCP = 0; ICP = 0; DCP = 0; CRDM = 0; CE = 0; LE = 0; CS = 0; LRI = 0;

    ui->reg_temp_4->setText(QString::number(temp_4, 16).toUpper());

    uc_4.cargar_ri(ui->reg_inst_4->text().toLong(&ok, 16));
    uc_4.cargar_temporizador(ui->reg_temp_4->text().toLong());

    //Cargar señales de control a la unidad de control
    uc_4.ejecutar_control(CA, LA, CB, LB, CF
                        ,LF, CRI, LRI, RT, CCP
                        ,LCP, ICP, DCP, EM, LM
                        ,CRDM, CE, LE, CS, OP);

    //Carga el contenido del Registro de Contador de Programa hacia el bus
    if (LCP == 1){
        ui->bus_principal->setText(ui->registro_cp->text());
        ui->bus_secundario_4->setText(ui->bus_principal->text());
    }
    else{

    }

    //Carga el contenido de la memoria al bus principal.
    if (LM == 1){
        i4 = ui->registro_dm->text().toLong(&ok, 16);
        ui->memoria_principal_4->setText(QString::number(memoria_n4[i4], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_4->text());
        ui->bus_secundario_4->setText(ui->bus_principal->text());
    }
    else{

    }

    //Carga el contenido del registro F hacia el bus principal.
    if (LF == 1){
        ui->bus_secundario_4->setText(ui->reg_f_4->text());
    }
    else{

    }

    //Carga el contenido del puerto de entrada al bus principal.
    if (LE == 1){
        ui->bus_principal->setText(ui->puerto_entrada->text().toUpper());
        ui->bus_secundario_4->setText(ui->bus_principal->text());
    }

    //Carga el contenido del bus principal al registro de contador de programa.
    if (CCP == 1){
        //ui->bus_principal->setText(ui->bus_secundario_4->text());
        ui->registro_cp->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus en el registro de direccionamiento de memoria.
    if (CRDM == 1){
        //ui->bus_principal->setText(ui->bus_secundario_4->text());
        ui->registro_dm->setText(ui->bus_principal->text());
    }
    else {

    }

    //Carga el contenido del bus hacia el registro de instrucciones.
    if (CRI == 1){
        ui->bus_secundario_4->setText(ui->bus_principal->text());
        ui->reg_inst_4->setText(ui->bus_secundario_4->text());
        uc_4.cargar_ri(ui->reg_inst_4->text().toLong(&ok, 16));
    }
    else {

    }

    //Cargar el contenido del bus en el puerto de salida.
    if (CS == 1){
        ui->bus_principal->setText(ui->bus_secundario_4->text());
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
        ui->reg_a_4->setText(ui->bus_secundario_4->text());
        ual_4.cargar_a(ui->reg_a_4->text().toLong(&ok, 16));
    }
    else {

    }

    //Cargar contenido del bus principal hacia el registro B.
    if (CB == 1){
        ui->reg_b_4->setText(ui->bus_secundario_4->text());
        ual_4.cargar_b(ui->reg_b_4->text().toLong(&ok, 16));
    }
    else {

    }

    //Carga el código de operación de la unidad aritmético lógica.
    //ual.cargar_op(OP);
    ui->op_4->setText(QString::number(ual_4.cargar_op(OP), 10).toUpper());

    //Cargan funcion de la unidad aritmético lógica
    ual_4.operacion(_F, _indicadores);

    //Carga un registro en la memoria.
    if (EM == 1){

        i4 = ui->registro_dm->text().toLong();
        ui->memoria_principal_4->setText(QString::number(memoria_n4[i4], 16).toUpper());
        ui->bus_principal->setText(ui->memoria_principal_4->text());
        ui->bus_secundario_4->setText(ui->bus_principal->text());
    }
    else{

    }

    //Cargar contenido en el registro F.
    if (CF == 1){
        ui->op_4->setText(QString::number(ual_4.cargar_op(OP), 10).toUpper());
        ual_4.operacion(_F, _indicadores);
        ui->reg_f_4->setText(QString::number(_F, 16).toUpper());

    }
    else {

    }

    //Incrementar registro contador de programa.
    if (ICP == 1){
        ui->registro_cp->setText(QString::number(incrementar(ui->registro_cp->text().toLong(&ok, 16)), 16).toUpper());
    }
    else {

    }

    //Decrementar registro contador de programa.
    if (DCP == 1){
        ui->registro_cp->setText(QString::number(decrementar(ui->registro_cp->text().toLong(&ok, 16)), 16).toUpper());
    }
    else {

    }

    //Reinicio del registro temporizador.
    if (RT == 1){
        ui->reg_temp_4->setText("0");
        temp_4 = 0;
    }
    else {
        temp_4 = ui->reg_temp_4->text().toLong();
        ++temp_4;
    }
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
    asignar_nucleo(turno);
    X1 = false; X2 = false; X3 = false; X4 = false;
    ab.turno_nucleo(turno, X1, X2, X3, X4);

    cout << turno << endl;

    if (X1 == true){
        ui->registro_cp->setText(QString::number(registro_cp1, 16).toUpper());
        ui->registro_dm->setText(QString::number(registro_dm1, 16).toUpper());
        ejecutar_n1();
        registro_cp1 = ui->registro_cp->text().toLong(&ok, 16);
        registro_dm1 = ui->registro_dm->text().toLong(&ok, 16);
    }

    if (X2 == true){
        ui->registro_cp->setText(QString::number(registro_cp2, 16).toUpper());
        ui->registro_dm->setText(QString::number(registro_dm2, 16).toUpper());
        ejecutar_n2();
        registro_cp2 = ui->registro_cp->text().toLong(&ok, 16);
        registro_dm2 = ui->registro_dm->text().toLong(&ok, 16);
    }

    if (X3 == true){
        ui->registro_cp->setText(QString::number(registro_cp3, 16).toUpper());
        ui->registro_dm->setText(QString::number(registro_dm3, 16).toUpper());
        ejecutar_n3();
        registro_cp3 = ui->registro_cp->text().toLong(&ok, 16);
        registro_dm3 = ui->registro_dm->text().toLong(&ok, 16);

    }

    if (X4 == true){
        ui->registro_cp->setText(QString::number(registro_cp4, 16).toUpper());
        ui->registro_dm->setText(QString::number(registro_dm4, 16).toUpper());
        ejecutar_n4();
        registro_cp4 = ui->registro_cp->text().toLong(&ok, 16);
        registro_dm4 = ui->registro_dm->text().toLong(&ok, 16);
    }

    reloj++;
    QString reloj_hex = QString::number(reloj, 16).toUpper();
    ui->reloj->setText(reloj_hex);

}

void simulador_computador::on_actionInstrucci_n_triggered()
{
    proxima_instruccion_n1();
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

    i = 0; i2 = 0; i3 = 0; i4 = 0;

    for (int j = 0; j < 255; j++){
        memoria[j] = 0;
        memoria_n2[j] = 0;
        memoria_n3[j] = 0;
        memoria_n4[j] = 0;
    }

    reloj = 0; turno = 0;
    temp = 0; temp_2 = 0; temp_3 = 0; temp_4 = 0;
    registro_cp1 = 0; registro_cp2 = 0; registro_cp3 = 0; registro_cp4 = 0;
    registro_dm1 = 0; registro_dm2 = 0; registro_dm3 = 0; registro_dm4 = 0;

}

void simulador_computador::on_actionSimular_triggered()
{
    cargar_codigo_n1();
    cargar_codigo_n2();
    cargar_codigo_n3();
    cargar_codigo_n4();
}

long simulador_computador::incrementar(long valor){
    long incremento;
    valor++;
    incremento = valor;
    return incremento;
}

long simulador_computador::decrementar(long valor){
    long decremento;
    valor--;
    decremento = valor;
    return decremento;
}

void simulador_computador::proxima_instruccion_n1(){
    int instruccion;
    ejecutar_n1();

    do {
        ejecutar_n1();
        instruccion = ui->reg_temp_1->text().toInt();
    } while (instruccion != 0);

}

void simulador_computador::cargar_codigo_n1(){
    char xy[20];
    long i;
    long int valor;

    ifstream archivo_objeto("codigo_objeto_n1.dat");

    archivo_objeto.getline(xy,20);
    i = atol(xy);

    while (!archivo_objeto.eof()){
        archivo_objeto.getline(xy,20);
        valor = strtol(xy,NULL,0);
        memoria[i] = valor;
        i++;
        cout << valor << endl;
    }

    archivo_objeto.close();
}

void simulador_computador::cargar_codigo_n2(){
    char xy[20];
    long i2;
    long int valor;

    ifstream archivo_objeto("codigo_objeto_n2.dat");

    archivo_objeto.getline(xy,20);
    i2 = atol(xy);

    while (!archivo_objeto.eof()){
        archivo_objeto.getline(xy,20);
        valor = strtol(xy,NULL,0);
        memoria_n2[i2] = valor;
        i2++;
    }

    archivo_objeto.close();
}

void simulador_computador::cargar_codigo_n3(){
    char xy[20];
    long i3;
    long int valor;

    ifstream archivo_objeto("codigo_objeto_n3.dat");

    archivo_objeto.getline(xy,20);
    i3 = atol(xy);

    while (!archivo_objeto.eof()){
        archivo_objeto.getline(xy,20);
        valor = strtol(xy,NULL,0);
        memoria_n3[i3] = valor;
        i3++;
    }

    archivo_objeto.close();
}

void simulador_computador::cargar_codigo_n4(){
    char xy[20];
    long i4;
    long int valor;

    ifstream archivo_objeto("codigo_objeto_n4.dat");

    archivo_objeto.getline(xy,20);
    i4 = atol(xy);

    while (!archivo_objeto.eof()){
        archivo_objeto.getline(xy,20);
        valor = strtol(xy,NULL,0);
        memoria_n4[i4] = valor;
        i4++;
    }

    archivo_objeto.close();
}

void simulador_computador::asignar_nucleo(int &_nucleo){

    if ((nucleo == 0) || (nucleo >= 5)){
        nucleo = 1;
    }

    if ((nucleo > 0) && (nucleo < 5)){
        nucleo++;
    }
    _nucleo = nucleo;
}

void simulador_computador::ejecutar_pulsos(){

    asignar_nucleo(turno);
    ab.turno_nucleo(turno, X1, X2, X3, X4);

    if (X1 == 1){
        ejecutar_n1();
    }

    if (X2 == 1){
        ejecutar_n2();
    }

    if (X3 == 1){
        ejecutar_n3();
    }

    if (X4 == 1){
        ejecutar_n4();
    }

}

