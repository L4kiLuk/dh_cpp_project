
#if !defined(Matchfield_C)
#define Matchfield_C

#include "Matchfield.hpp"
#include <string>
#include <iostream> 



//noch unvollständig, bei erfolgreichem Zug bitte changeActualPlayer aufrufen. Den Methodenaufruf dann aus Contoller startGame() ausbauen.
bool Matchfield::move(Coordinates_t from, Coordinates_t to){
    //kontrolle
    if(field[from.x][from.y] == NULL ){
        std::cout << "Fehler, Spielstein position ungültig"; //Bitte als exeption oder so. Das kann die Anzeige zerstören. Schreiben sollte nur der Controller.
        return false;
    }else {
        //black -> nach unten
        if ((to.x==from.x+1)&&(to.y==from.y-1||to.y==from.y+1) && field[to.x][to.y] == NULL && field[from.x][from.y]->black==true)
        {
            field[to.x][to.y]=field[from.x][from.y];
            field[from.x][from.y] = NULL;
            changeActualPlayer();
            return true;
        }
        else if((to.x==from.x+2)&&(to.y==from.y-2||to.y==from.y+2)&&field[to.x][to.y]==NULL&& field[from.x+(to.x-from.x)][from.y+(to.y-from.y)]->black!=field[from.x][from.y]->black && field[from.x][from.y]->black==true){
            field[to.x][to.y]=field[from.x][from.y];
            field[from.x][from.y] = NULL;
            field[from.x+(to.x-from.x)][from.y+(to.y-from.y)] = NULL;
            //check for another move
            changeActualPlayer();
            return true;

        }
        //weiß unten nach oben
        else if ((to.x==from.x-1)&&(to.y==from.y-1||to.y==from.y+1) && field[to.x][to.y] == NULL && field[from.x][from.y]->black==true)
        {
            field[to.x][to.y]=field[from.x][from.y];
            field[from.x][from.y] = NULL;
            changeActualPlayer();
            return true;
        }
        else if((to.x==from.x-2)&&(to.y==from.y-2||to.y==from.y+2)&&field[to.x][to.y]==NULL&& field[from.x+(to.x-from.x)][from.y+(to.y-from.y)]->black!=field[from.x][from.y]->black && field[from.x][from.y]->black==true){
            field[to.x][to.y]=field[from.x][from.y];
            field[from.x][from.y] = NULL;
            field[from.x+(to.x-from.x)][from.y+(to.y-from.y)] = NULL;
            //check for another move
            changeActualPlayer();
            return true;

        }
        
    }

}

//noch unvollständig
Coordinates_t* Matchfield::hint(Coordinates_t from){

}



void Matchfield::init(){
    actualPlayer=0;
    //oben (0,1,3 black, unten 5,6,7 weiß)
    // zweite variable ist links(0) nach rechts (7)
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(i==0&&((j%2)==1)){
                field[i][j] = new Stone(false, true);
            }else
            if(i==1&&((j%2)==0)){
                field[i][j] = new Stone(false, true);
            }else 
            if(i==2&&((j%2)==1)){
                field[i][j] = new Stone(false, true);
            }else
            if(i==5&&((j%2)==0)){
                field[i][j] = new Stone(false, false);
            }else 
            if(i==6&&((j%2)==1)){
                field[i][j] = new Stone(false, false);
            }else
            if(i==7&&((j%2)==0)){
                field[i][j] = new Stone(false, false);
            }else {
                field[i][j] = NULL;
            }
        }
        
    }
    
}

    void Matchfield::changeActualPlayer(){
        actualPlayer=++actualPlayer%2;
    }

    int Matchfield::getActualPlayer(){
        return actualPlayer;
    }
    void Matchfield::setActualPlayer(int player){
        actualPlayer=player;
    }
#endif // SPIELFELD
