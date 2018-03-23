/** Arbitro de bus **/

#include "arbitro_de_bus.h"

ARBITRO_DE_BUS::ARBITRO_DE_BUS(){}

ARBITRO_DE_BUS::~ARBITRO_DE_BUS(){}

void ARBITRO_DE_BUS::turno_nucleo(int _nucleo, bool &_x1, bool &_x2, bool &_x3, bool &_x4){

    x1 = false; x2 = false; x3 = false; x4 = false;

    switch (_nucleo){
        case 2: x1 = true; break;
        case 3: x2 = true; break;
        case 4: x3 = true; break;
        case 5: x4 = true; break;
        default: break;
    }

    _x1 = x1; _x2 = x2;
    _x3 = x3; _x4 = x4;
}
