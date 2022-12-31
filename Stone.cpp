#ifndef Stone_C
#define Stone_C
#include "Stone.hpp"


Stone::Stone(bool z, bool s)
{
    state = z;//enum : normal, dame, hint
    black = s;
    
}
#endif //SPIELSTEINH