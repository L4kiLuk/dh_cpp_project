#ifndef Spielfeld_c
#define Spielfeld_C

#include "Spielstein.cpp"
#include <string>

struct Koordinaten
{
    int x;
    int y;
    Koordinaten(int px,int py): x(px),y(py){}
}typedef Koordinaten_t;

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