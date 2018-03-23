#ifndef ARBITRO_DE_BUS_H
#define ARBITRO_DE_BUS_H

#include <iostream>

class ARBITRO_DE_BUS
{
public:
    ARBITRO_DE_BUS();
    ~ARBITRO_DE_BUS();
    void turno_nucleo(int, bool&, bool&, bool&, bool&);

private:
    bool x1, x2, x3, x4;
    int nucleo;
};

#endif // ARBITRO_DE_BUS_H
