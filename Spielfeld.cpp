
#if !defined(SPIELFELD)
#define SPIELFELD

#include "Spielfeld.hpp"
#include <string>
#include <iostream> 



//noch unvollständig, bei erfolgreichem Zug bitte changeActualPlayer aufrufen. Den Methodenaufruf dann aus Contoller startGame() ausbauen.
bool Spielfeld::move(Koordinaten_t from, Koordinaten_t to){
    //kontrolle
    if(feld[from.x][from.y] == NULL ){
        std::cout << "Fehler, Spielstein position ungültig"; //Bitte als exeption oder so. Das kann die Anzeige zerstören. Schreiben sollte nur der Controller.
        return false;
    }else {
        //schwarz -> nach unten
        if ((to.x==from.x+1)&&(to.y==from.y-1||to.y==from.y+1) && feld[to.x][to.y] == NULL && feld[from.x][from.y]->schwarz==true)
        {
            feld[to.x][to.y]=feld[from.x][from.y];
            feld[from.x][from.y] = NULL;
            return true;
        }
        else if((to.x==from.x+2)&&(to.y==from.y-2||to.y==from.y+2)&&feld[to.x][to.y]==NULL&& feld[from.x+(to.x-from.x)][from.y+(to.y-from.y)]->schwarz!=feld[from.x][from.y]->schwarz && feld[from.x][from.y]->schwarz==true){
            feld[to.x][to.y]=feld[from.x][from.y];
            feld[from.x][from.y] = NULL;
            feld[from.x+(to.x-from.x)][from.y+(to.y-from.y)] = NULL;
            return true;

        }
        //weiß unten nach oben
        else if ((to.x==from.x-1)&&(to.y==from.y-1||to.y==from.y+1) && feld[to.x][to.y] == NULL && feld[from.x][from.y]->schwarz==true)
        {
            feld[to.x][to.y]=feld[from.x][from.y];
            feld[from.x][from.y] = NULL;
            return true;
        }
        else if((to.x==from.x-2)&&(to.y==from.y-2||to.y==from.y+2)&&feld[to.x][to.y]==NULL&& feld[from.x+(to.x-from.x)][from.y+(to.y-from.y)]->schwarz!=feld[from.x][from.y]->schwarz && feld[from.x][from.y]->schwarz==true){
            feld[to.x][to.y]=feld[from.x][from.y];
            feld[from.x][from.y] = NULL;
            feld[from.x+(to.x-from.x)][from.y+(to.y-from.y)] = NULL;
            return true;

        }
        
    }

}

//noch unvollständig
Koordinaten_t* Spielfeld::hint(Koordinaten_t from){

}



void Spielfeld::init(){
    actualPlayer=0;
    //oben (0,1,3 schwarz, unten 5,6,7 weiß)
    // zweite variable ist links(0) nach rechts (7)
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(i==0&&((j%2)==1)){
                feld[i][j] = new Spielstein(false, true);
            }else
            if(i==1&&((j%2)==0)){
                feld[i][j] = new Spielstein(false, true);
            }else 
            if(i==2&&((j%2)==1)){
                feld[i][j] = new Spielstein(false, true);
            }else
            if(i==5&&((j%2)==0)){
                feld[i][j] = new Spielstein(false, false);
            }else 
            if(i==6&&((j%2)==1)){
                feld[i][j] = new Spielstein(false, false);
            }else
            if(i==7&&((j%2)==0)){
                feld[i][j] = new Spielstein(false, false);
            }else {
                feld[i][j] = NULL;
            }
        }
        
    }
    
}

    void Spielfeld::changeActualPlayer(){
        actualPlayer=++actualPlayer%2;
    }

    int Spielfeld::getActualPlayer(){
        return actualPlayer;
    }
#endif // SPIELFELD
