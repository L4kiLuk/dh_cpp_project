#ifndef SPIELSTEINH
#define SPIELSTEINH
#include "Spielstein.hpp"


Spielstein::Spielstein(bool z, bool s)
{
    zustand = z;//enum : normal, dame, hint
    schwarz = s;
    
}
#endif //SPIELSTEINH