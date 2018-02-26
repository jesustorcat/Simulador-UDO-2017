#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#define max_inst 256 //Máximo número de instrucciones

using namespace std;

class compilador_sintactico
{
public:
    compilador_sintactico();
    ~compilador_sintactico();
    int analisis_sintactico();

private:
    char etiqueta[15], direccion[15], operando[15], op[15], simbolo[80][15], simb_dir[80][15], tmp[max_inst];
    int buff, buff1, longitud, i, j, lc, n, f1;
    char *buff2;
    char *pop;

};

#endif // ANALIZADOR_SINTACTICO_H
