/** Arbitro de bus **/

#include "arbitro_de_bus.h"

ARBITRO_DE_BUS::ARBITRO_DE_BUS(){}

ARBITRO_DE_BUS::~ARBITRO_DE_BUS(){}

void ARBITRO_DE_BUS::turno_nucleo(int &_nucleo){

    switch (_nucleo){
        case 1: x1 = 1; break;
        case 2: x2 = 1; break;
        case 3: x3 = 1; break;
        case 4: x4 = 1; break;
        default: _nucleo = 1; break;
    }
}
