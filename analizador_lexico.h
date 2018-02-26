#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#define inst_max 256 //Máxino número de instrucciones

using namespace std;

class compilador
{
public:
    compilador();
    ~compilador();
    int analisis_lexico(string);

private:
    char nombre[80];
    char tmp[inst_max];
    char respaldo[inst_max];
    char b[20][10];
    int i, lc, s, l, f, f1, n;
    char *buff;
    char *buff1;
};

#endif // ANALIZADOR_LEXICO_H
