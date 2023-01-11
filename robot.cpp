#if !defined(ROBOT)
#define ROBOT

#include "robot.hpp"



void Robot::nextMove(){
    std::vector<PossibleMove> possmoves;
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(matchfield->field[x][y]!=NULL){
                if(matchfield->field[x][y]->black){
                    std::vector<PossibleMove> moves = findMoves(Coordinates(x,y));
                    for(PossibleMove move:moves){
                        if(move.benefit>bestMove.benefit){
                            bestMove=move;
                        }
                    }
                }
            }
        }
    }
   matchfield->move(bestMove.from,bestMove.to);
}

std::vector<PossibleMove> Robot::findMoves(Coordinates from){
    std::vector<PossibleMove> moves;
    
    if(matchfield->field[from.x][from.y]->state){
        //Dame
    }else{
        //Normal
        int nextX = from.x+1;
        int nextY = from.y+1;
        if(nextX<8&&nextY<8)
        if(matchfield->field[nextX][nextY]==NULL){
            moves.push_back(PossibleMove(from,Coordinates(nextX,nextY),0));
        }else if(!matchfield->field[nextX][nextY]->black){
            for(PossibleMove move:findMoves(Coordinates(nextX,nextY))){
                moves.push_back(move);
            }
        } 
        nextY = from.y-1;
        if(nextX<8&&nextY>=0)
        if(matchfield->field[nextX][nextY]==NULL){
            moves.push_back(PossibleMove(from,Coordinates(nextX,nextY),0));
        }else if(!matchfield->field[nextX][nextY]->black){
            for(PossibleMove move:findMoves(Coordinates(nextX,nextY))){
                moves.push_back(move);
            }
        } 
    }
    
    return moves;
}


#endif // ROBOT
