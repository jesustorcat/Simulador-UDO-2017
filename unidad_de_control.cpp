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
