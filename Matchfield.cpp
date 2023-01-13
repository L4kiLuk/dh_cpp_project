
#if !defined(Matchfield_C)
#define Matchfield_C

#include "Exceptions.hpp"
#include "Matchfield.hpp"
#include <string>
#include <iostream> 
#include <vector>



//noch unvollständig, bei erfolgreichem Zug bitte changeActualPlayer aufrufen. Den Methodenaufruf dann aus Contoller startGame() ausbauen.
void Matchfield::move(Coordinates_t from, Coordinates_t to){
    //kontrolle
    
    if(field[from.x][from.y] == NULL || field[to.x][to.y]!=NULL ){
        //std::cout << "Fehler, Spielstein position ungültig"; //Bitte als exeption oder so. Das kann die Anzeige zerstören. Schreiben sollte nur der Controller.
        throw WrongMoveException();
    }else {
        if(field[from.x][from.y]->black==actualPlayer){
            throw WrongMoveException();
        }

        int movesblack = 0;
        int moveswhite = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if(field[i][j]!= NULL){
                    if(field[i][j]->black){
                        
                    movesblack += hint(Coordinates_t(i,j)).size();
                    }
                    else if(!field[i][j]->black){
                        moveswhite += hint(Coordinates_t(i,j)).size();
                    }
                }
                
            }
            
        }
        if (movesblack == 0 || moveswhite ==0)
        {
            throw GameEndException();
        }

        //weiß zu Dame
        if(field[from.x][from.y]->black==false &&  field[from.x][from.y]->state==false && actualPlayer == 0 && from.y == 1 && to.y ==0){
            field[from.x][from.y]-> state = true;
        }
        //schwarz zu Dame 
        else if(field[from.x][from.y]->black==true &&  field[from.x][from.y]->state==false && actualPlayer == 1 && from.y == 6 && to.y ==7){
            field[from.x][from.y]-> state = true;
        }
        //black -> nach unten
        if (actualPlayer==0 &&(to.x==from.x+1)&&(to.y==from.y-1||to.y==from.y+1) && field[to.x][to.y] == NULL && field[from.x][from.y]->black==true)
        {
            field[to.x][to.y]=field[from.x][from.y];
            field[from.x][from.y]->~Stone();
            field[from.x][from.y] = NULL;
            changeActualPlayer();
            
        }
        else if(actualPlayer==0 &&(to.x==from.x+2)&&(to.y==from.y-2||to.y==from.y+2)&&field[to.x][to.y]==NULL&& field[from.x+((to.x-from.x)/2)][from.y+((to.y-from.y)/2)]->black==false && field[from.x][from.y]->black==true){
            field[to.x][to.y]=field[from.x][from.y];
            field[from.x][from.y]->~Stone();
            field[from.x][from.y] = NULL;
            field[from.x+((to.x-from.x)/2)][from.y+((to.y-from.y)/2)]->~Stone();
            field[from.x+((to.x-from.x)/2)][from.y+((to.y-from.y)/2)] = NULL;
            //check for another move
            if(hint(to, true).size() == 0){
                changeActualPlayer();
            }

        }
        //weiß unten nach oben
        else if (actualPlayer==1 &&(to.x==from.x-1)&&(to.y==from.y-1||to.y==from.y+1) && field[to.x][to.y] == NULL && field[from.x][from.y]->black==false)
        {
            field[to.x][to.y]=field[from.x][from.y];
            field[from.x][from.y]->~Stone();
            field[from.x][from.y] = NULL;
            changeActualPlayer();
        }
        else if(actualPlayer==1 &&(to.x==from.x-2)&&(to.y==from.y-2||to.y==from.y+2)&&field[to.x][to.y]==NULL&& field[from.x+((to.x-from.x)/2)][from.y+((to.y-from.y)/2)]->black!=field[from.x][from.y]->black && field[from.x][from.y]->black==false){
            field[to.x][to.y]=field[from.x][from.y];
            field[from.x][from.y]->~Stone();
            field[from.x][from.y] = NULL;
            field[from.x+((to.x-from.x)/2)][from.y+((to.y-from.y)/2)]->~Stone();
            field[from.x+((to.x-from.x)/2)][from.y+((to.y-from.y)/2)] = NULL;
            //check for another move
            if(hint(to, true).size() == 0){
                changeActualPlayer();
            }
        
        } //dame
        else if(field[from.x][from.y]->state == true && field[from.x][from.y]->black==!actualPlayer){
            for(Coordinates_t coord : hint(from)){
                if(coord.x == to.x && coord.y == to.y){
                    if(hint(to, true).size() == 0){
                        changeActualPlayer();
                    }
                }
            }
        }
        
        //throw WrongMoveException();
        
        
        
    }

}

std::vector<Coordinates_t> Matchfield::hint(Coordinates_t from){
    return hint(from, false);
}

//noch unvollständig
std::vector<Coordinates> Matchfield::hint(Coordinates_t from, bool beat_only){
    std::vector<Coordinates_t> vector;
    if(field[from.x][from.y]==NULL){
        return vector;
    }
    //weiß schlagen
    if(field[from.x-1][from.y-1]!=NULL&&from.y>1&&from.x>1){
        if(field[from.x][from.y]->state==false&&field[from.x][from.y]->black==false&&field[from.x-1][from.y-1]->black==true&&field[from.x-2][from.y-2]==NULL){
            vector.push_back(Coordinates_t(from.x-2, from.y-2));
        }
    }
    if(field[from.x-1][from.y+1]!=NULL&&from.y<6&&from.x>1){
        if(field[from.x][from.y]->state==false&&field[from.x][from.y]->black==false&&field[from.x-1][from.y+1]->black==true&&field[from.x-2][from.y+2]==NULL){
            vector.push_back(Coordinates_t(from.x-2, from.y-2));
        }
    }
    //schwarz schlagen
    if(field[from.x+1][from.y-1]!=NULL&&from.y>1&&from.x<6){
        if(field[from.x][from.y]->state==false&&field[from.x][from.y]->black==true&&field[from.x+1][from.y-1]->black==false&&field[from.x+2][from.y-2]==NULL){
            vector.push_back(Coordinates_t(from.x-2, from.y+2));
        }
    }
    if(field[from.x+1][from.y+1]!=NULL&&from.y<6&&from.x<6){
        if(field[from.x][from.y]->state==false&&field[from.x][from.y]->black==true&&field[from.x+1][from.y+1]->black==false&&field[from.x+2][from.y+2]==NULL){
            vector.push_back(Coordinates_t(from.x-2, from.y+2));
        }
    }

    if(beat_only == true){
          return vector;
    }
    
    //schwarz normal
    if(from.x<7&&from.y>0){
        if(field[from.x][from.y]->state==false&&field[from.x][from.y]->black==true&&field[from.x+1][from.y-1]==NULL){
            vector.push_back(Coordinates_t(from.x+1, from.y-1));
        }
    }
    if(from.x<7&&from.y<7){
        if(field[from.x][from.y]->state==false&&field[from.x][from.y]->black==true&&field[from.x+1][from.y+1]==NULL){
            vector.push_back(Coordinates_t(from.x+1, from.y+1));
        }
    }
    
    //weiß normal
    if(from.x<7&&from.y<7){
        if(field[from.x][from.y]->state==false&&field[from.x][from.y]->black==false&&field[from.x-1][from.y+1]==NULL){
            vector.push_back(Coordinates_t(from.x-1, from.y+1));
        }
    }
    if(from.x>0&&from.y>0){
        if(field[from.x][from.y]->state==false&&field[from.x][from.y]->black==false&&field[from.x-1][from.y-1]==NULL){
            vector.push_back(Coordinates_t(from.x-1, from.y-1));
        }
    }
    
    
    if(field[from.x][from.y]->state == true){
         //schwarz dame
        //weiß dame
        int maxSteps;
        int maxX;
        int maxY;
        //ÜBERARBEITEN!! Alle 4 richtungen checken aber nicht übern rand raus
        //unten rechts

        maxX = 7-from.x;
        maxY = 7-from.y;
        maxSteps = (maxX<maxY)?maxX:maxY;
        for(int i = 0; i<maxSteps; i++){
            if(field[from.x+i][from.y+i]==NULL&&beat_only==false){
                vector.push_back(Coordinates_t(from.x+i, from.y+i));
            }else if(field[from.x+i+1][from.y+i+1]==NULL&&field[from.x+i][from.y+i]->black==!field[from.x][from.y]->black){
                vector.push_back(Coordinates_t(from.x+i+1, from.y+i+1));
                break;
            }
        }
        //unten links
        maxX = from.x;
        maxY = 7-from.y;
        maxSteps = (maxX<maxY)?maxX:maxY;
        for(int i = 0; i<maxSteps; i++){
            if(field[from.x-i][from.y+i]==NULL&&beat_only==false){
                vector.push_back(Coordinates_t(from.x-i, from.y+i));
            }else if(field[from.x-i-1][from.y+i+1]==NULL&&field[from.x-i][from.y+i]->black==!field[from.x][from.y]->black){
                vector.push_back(Coordinates_t(from.x-i-1, from.y+i+1));
                break;
            }
        }
        //oben rechts 
        maxX = 7-from.x;
        maxY = from.y;
        maxSteps = (maxX<maxY)?maxX:maxY;
        for(int i = 0; i<maxSteps; i++){
            if(field[from.x+i][from.y-i]==NULL&&beat_only==false){
                vector.push_back(Coordinates_t(from.x+i, from.y-i));
            }else if(field[from.x+i+1][from.y-i-1]==NULL&&field[from.x+i][from.y+i]->black==!field[from.x][from.y]->black){
                vector.push_back(Coordinates_t(from.x+i+1, from.y-i-1));
                break;
            }
        }
        //oben links
        maxX = from.x;
        maxY = from.y;
        maxSteps = (maxX<maxY)?maxX:maxY;
        for(int i = 0; i<maxSteps; i++){
            if(field[from.x-i][from.y-i]==NULL&&beat_only==false){
                vector.push_back(Coordinates_t(from.x-i, from.y-i));
            }else if(field[from.x-i-1][from.y-i-1]==NULL&&field[from.x-i][from.y-i]->black==!field[from.x][from.y]->black){
                vector.push_back(Coordinates_t(from.x-i-1, from.y-i-1));
                break;
            }
        }
    }
   
    int i = 0;
    return vector;
}



void Matchfield::init(){
    actualPlayer=0;
    //oben (0,1,3 black, unten 5,6,7 weiß)
    // zweite variable ist links(0) nach rechts (7)
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(j==0&&((i%2)==1)){
                field[j][i] = new Stone(false, true);
            }else
            if(j==1&&((i%2)==0)){
                field[j][i] = new Stone(false, true);
            }else 
            if(j==2&&((i%2)==1)){
                field[j][i] = new Stone(false, true);
            }else
            if(j==5&&((i%2)==0)){
                field[j][i] = new Stone(false, false);
            }else 
            if(j==6&&((i%2)==1)){
                field[j][i] = new Stone(false, false);
            }else
            if(j==7&&((i%2)==0)){
                field[j][i] = new Stone(false, false);
            }else {
                field[j][i] = NULL;
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
