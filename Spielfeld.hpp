#ifndef Spielfeld_c
#define Spielfeld_C

#include "Spielstein.hpp"
#include <string>

class Spielfeld
{
private:
    
public:
struct Koordinaten;
    Spielstein* feld[8][8];
    bool move(Koordinaten_t from, Koordinaten_t to);
    Koordinaten_t* hint(Koordinaten_t from);
    void init();
    //Spielfeld(/* args */);
    //~Spielfeld();
};

//Spielfeld::Spielfeld(/* args */)
/*{

}

Spielfeld::~Spielfeld()
{
}*/


#endif