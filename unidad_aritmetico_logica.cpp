/** Unidad Aritmetico lógica **/

#include "unidad_aritmetico_logica.h"
#define VALOR_MAX 4294967295 //32 bits

using namespace std;

UNIDAD_ARITMETICO_LOGICA::UNIDAD_ARITMETICO_LOGICA(){}

UNIDAD_ARITMETICO_LOGICA::~UNIDAD_ARITMETICO_LOGICA(){}

void UNIDAD_ARITMETICO_LOGICA::cargar_a(long valor_a){
    A=valor_a;
}

void UNIDAD_ARITMETICO_LOGICA::cargar_b(long valor_b){
    B=valor_b;
}

int UNIDAD_ARITMETICO_LOGICA::cargar_op(int valor_op){
    op=valor_op;
    return op;
}

long UNIDAD_ARITMETICO_LOGICA::operacion(long& vf, long& vi){

    switch (op) {
        case 0: F = A+B; break;
        case 1 : F = A-B; break;
        case 2 : F = A+1; break;
        case 3 : F = A-1; break;
        case 4 : F = A*B; break;
        case 5 : if(B!=0){
        F = ((double)A)/B;
             } else {
            F = VALOR_MAX;
        }   break;
        case 6 : F = pow(A,2); break;
        case 7 : F = sqrt(A); break;
        case 8 : F = A; break;
        case 9 : F = B; break;
        case 10 : F = 0; break;
        case 11 : F = VALOR_MAX; break;
        case 12 : F = log((double)A); break;
        case 13 : F = log10((double)A); break;
        case 14 : F = exp((double)A); break;
        case 15 : F = (A|B) & VALOR_MAX; break;
        case 16 : F = (A&B) & VALOR_MAX; break;
        case 17 : F = (A^B) & VALOR_MAX; break;
        case 18 : F = (~A) & VALOR_MAX; break;
        case 19 : F = (A>>1) & VALOR_MAX; break;
        case 20 : F = (A<<1) & VALOR_MAX; break;

        default: F=0; break;
    }

    if(op==9)
        indicador = B;
    else
        indicador = indicadores(F);

    vf=F;
    vi=indicador;

    return F;
}

long UNIDAD_ARITMETICO_LOGICA::indicadores(long valor){
    long banderas;
    (valor == 0) ? z = 1 : z = 0;
    (valor < 0) ? s = 1 : s = 0;
    (labs(valor) > VALOR_MAX) ? d = 1 : d = 0;
    p = (((valor&4294967296)>>32) ^ ((valor&2147483648)>>31) ^ ((valor&1073741824)>>30) ^ ((valor&536870912)>>29)
           ^ ((valor&268435456)>>28) ^ ((valor&134217728)>>27) ^ ((valor&67108864)>>26) ^ ((valor&33554432)>>25)
           ^ ((valor&16777216)>>24) ^ ((valor&8388608)>>23) ^ ((valor&4194304)>>22) ^ ((valor&2097152)>>21)
           ^ ((valor&1048576)>>20) ^ ((valor&524288)>>19) ^ ((valor&262144)>>18) ^ ((valor&131072)>>17)
           ^ ((valor&65536)>>16) ^ ((valor&32768)>>15) ^ ((valor&16384)>>14) ^ ((valor&8192)>>13)
           ^ ((valor&4096)>>12) ^ ((valor&2048)>>11) ^ ((valor&1024)>>10) ^ ((valor&512)>>9)
           ^ ((valor&256)>>8) ^ ((valor&128)>>7) ^ ((valor&64)>>6) ^ ((valor&32)>>5) ^ ((valor&16)>>4)
           ^ ((valor&8)>>3) ^ ((valor&4)>>2) ^ ((valor&2)>>1) ^ (valor&1));

    banderas = 8*z + 4*d + s*2 +1*p;
    return banderas;
}

















