/** Unidad de control **/

#include "unidad_de_control.h"

UNIDAD_DE_CONTROL::UNIDAD_DE_CONTROL(){}

UNIDAD_DE_CONTROL::~UNIDAD_DE_CONTROL(){}

/**
*
*/
void UNIDAD_DE_CONTROL::cargar_ri(long _ri){
    ri = _ri;
}

void UNIDAD_DE_CONTROL::cargar_temporizador(long int _temporizador){
    temporizador = _temporizador;
}

void UNIDAD_DE_CONTROL::cargar_indicadores(int _indicadores){
    indicadores = _indicadores;

    z = (_indicadores&0x8)>>3;
    d = (_indicadores&0x4)>>2;
    p = (_indicadores&0x2)>>1;
    s = (_indicadores&0x1);
}

void UNIDAD_DE_CONTROL::ejecutar_control(int &_Ca, int &_La, int &_Cb, int &_Lb, int &_Cf
                                         ,int &_Lf, int &_Cri, int &_Lri, int &_Rt, int &_Ccp
                                         ,int &_Lcp, int &_Icp, int &_Dcp, int &_Em, int &_Lm
                                         ,int &_Ce, int &_Le, int &_Cs){

    switch (temporizador){
        case 0: Crdm = 1; Lcp = 1; break;
        //case 1: ;break; Para asignar el núcleo
        case 2: Lm = 1; Cri = 1; Icp = 1; break;

        default:
            switch (ri){
                case 0: //Realiza un ciclo sin operar
                    switch (temporizador){
                        case 3: Rt = 1; break;
                    }
                case 1: //Mueve el contenido del puerto de entrada hacia el puerto de salida
                    switch (temporizador){
                        case 3: Cs = 1; Le = 1; Rt = 1; break;
                    }
                case 2: //Mueve el contenido del puerto de entrada hacia el registro “A”
                    switch (temporizador){
                        case 3: Ca = 1; Le = 1; Rt = 1; break;
                    }
                case 3: //Mueve el contenido del puerto de entrada hacia el registro “B”
                    switch (temporizador){
                        case 3: Cb = 1; Le = 1; Rt = 1; break;
                    }
                case 4: //Mueve el contenido del registro “F” hacia el registro “A”
                    switch (temporizador){
                        case 3: Ca = 1; Lf = 1; Rt = 1; break;
                    }
                case 5: //Mueve el contenido del registro “F” hacia el registro “B”
                    switch (temporizador){
                        case 3: Cb = 1; Lf = 1; Rt = 1; break;
                    }
                case 6: //Mueve el contenido del registro “A” hacia el registro “F”
                    switch (temporizador){
                        case 3: Cf = 1; op = 8; Rt = 1; break;
                    }
                case 7: //Mueve el contenido del registro “B” hacia el registro “F”
                    switch (temporizador){
                        case 3: Cf = 1; op = 9; Rt = 1; break;
                    }
                case 8: //Mueve el contenido del registro “F” hacia el puerto de salida
                    switch (temporizador){
                        case 3: Cs = 1; Lf = 1; Rt = 1; break;
                    }
                case 9: //Carga un dato de la memoria en el registro “A”
                    switch (temporizador){
                        case 3: Crdm = 1; Lcp = 1; break;
                        case 4: Ca = 1; Icp = 1; Lm = 1; Rt = 1; break;
                    }
                case 10: //Carga un dato de la memoria en el registro “B”
                    switch (temporizador){
                        case 3: Crdm = 1; Lcp = 1; break;
                        case 4: Cb = 1; Icp = 1; Lm = 1; Rt = 1; break;
                    }
                case 11: //Carga un dato de la memoria en el puerto de salida
                    switch (temporizador){
                        case 3: Crdm = 1; Lcp = 1; break;
                        case 4: Cs = 1; Icp = 1; Lm = 1; Rt = 1; break;
                    }
                case 12: //Suma los datos que se encuentren en los registros “A” y “B”
                    switch (temporizador){
                        case 3: Cf = 1; op = 0; Rt = 1; break;
                    }
                case 13: //Resta los datos que se encuentren en el registro “A” con los del registro “B”
                    switch (temporizador){
                        case 3: Cf = 1; op = 1; Rt = 1; break;
                    }
                case 14: //Multiplica los datos que se encuentren en el registro “A” con los del registro “B”
                    switch (temporizador){
                        case 3: Cf = 1; op = 4; Rt = 1; break;
                    }
                case 15: //Divide los datos que se encuentren en el registro “A” con los del registro “B”
                    switch (temporizador){
                        case 3: Cf = 1; op = 5; Rt = 1; break;
                    }
                case 16: //Realiza el incremento de un dato almacenado en el registro “A”
                    switch (temporizador){
                        case 3: Cf = 1; op = 2; Rt = 1; break;
                    }
                case 17: //Realiza el decremento de un dato almacenado en el registro “A”
                    switch (temporizador){
                        case 3: Cf = 1; op = 3; Rt = 1; break;
                    }
                case 18: //Eleva al cuadrado el dato del registro “A”
                    switch (temporizador){
                        case 3: Cf = 1; op = 6; Rt = 1; break;
                    }
                case 19: //Extrae la raíz cuadrada del dato del registro “A”
                    switch (temporizador){
                        case 3: Cf = 1; op = 7; Rt = 1; break;
                    }
                case 20: //Transfiere el dato del registro “A” al registro “F”
                    switch (temporizador){
                        case 3: Cf = 1; op = 8; Rt = 1; break;
                    }
                case 21: //Transfiere el dato del registro “B” al registro “F”
                    switch (temporizador){
                        case 3: Cf = 1; op = 9; Rt = 1; break;
                    }
                case 22: //SET
                    switch (temporizador){
                        case 3: Cf = 1; op = 10; Rt = 1; break;
                    }
                case 23: //RESET
                    switch (temporizador){
                        case 3: Cf = 1; op = 11; Rt = 1; break;
                    }
            }
    }
}
