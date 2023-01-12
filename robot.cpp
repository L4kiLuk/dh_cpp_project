#if !defined(ROBOT)
#define ROBOT

#include "robot.hpp"



void Robot::nextMove(){
    std::vector<PossibleMove> possmoves;
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(matchfield->field[x][y]!=NULL){
                if(matchfield->field[x][y]->black){
                    std::vector<PossibleMove> moves = findMoves(PossibleMove(Coordinates(x,y),Coordinates(x,y),-1),0);
                    for(PossibleMove move:moves){
                        if(move.benefit>bestMove.benefit){
                            bestMove=move;
                        }
                    }
                }
            }
        }
    }
   bool result = matchfield->move(bestMove.from,bestMove.to);
}

std::vector<PossibleMove> Robot::findMoves(PossibleMove posMove,int heading){//heading:0,No,1,Left,2,Right
    std::vector<PossibleMove> moves;
    
    if(matchfield->field[posMove.to.x][posMove.to.y]->state){
        //Dame
    }else{
        //Normal
        int nextX = posMove.to.x+1;
        int nextY = posMove.to.y+1;
        if(nextX<8&&nextY<8&&heading!=2)
        if(matchfield->field[nextX][nextY]==NULL){
            PossibleMove posMoveRight(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
            moves.push_back(posMoveRight);
        }else if(!matchfield->field[nextX][nextY]->black){
            PossibleMove posMoveRight(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
            for(PossibleMove move:findMoves(posMoveRight,1)){
                moves.push_back(move);
            }
        } 
        nextY = posMove.to.y-1;
        if(nextX<8&&nextY>=0&&heading!=1)
        if(matchfield->field[nextX][nextY]==NULL){
            PossibleMove posMoveLeft(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
            moves.push_back(posMoveLeft);
        }else if(!matchfield->field[nextX][nextY]->black){
            PossibleMove posMoveLeft(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
            for(PossibleMove move:findMoves(posMoveLeft,2)){
                moves.push_back(move);
            }
        } 
    }
    
    return moves;
}


#endif // ROBOT
