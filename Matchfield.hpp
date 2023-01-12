#ifndef Matchfield_H
#define Matchfield_H

#include "Stone.cpp"
#include <string>
#include <vector>

struct Coordinates
{
    int x;
    int y;
    Coordinates(int px,int py): x(px),y(py){}
}typedef Coordinates_t;

class Matchfield
{
private:
    int actualPlayer; //Track which player has the next move
    
public:
struct Coordinates;
    Stone* field[8][8];
    void move(Coordinates_t from, Coordinates_t to);
    std::vector<Coordinates_t> hint(Coordinates_t from, bool beat_only);
    std::vector<Coordinates_t> hint(Coordinates_t from);
    void init();
    void changeActualPlayer(); //gerne in move() einbauen nach einem erfolgreichen Zug, dann kann ich es aus dem Controller nehmen.
    int getActualPlayer();
    void setActualPlayer(int player);
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
