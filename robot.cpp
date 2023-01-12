#if !defined(ROBOT)
#define ROBOT

#include "robot.hpp"



void Robot::nextMove(){
    std::vector<PossibleMove> possmoves;
    PossibleMove bestMove=PossibleMove(Coordinates(0,0),Coordinates(0,0));
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(matchfield->field[x][y]!=NULL){
                if(matchfield->field[x][y]->black){
                    std::vector<PossibleMove> moves = findMoves(PossibleMove(Coordinates(x,y),Coordinates(x,y),-1),0);
                    for(PossibleMove move:moves){
                        if(move.benefit>bestMove.benefit){
                            bestMove=move;
                        }
                        possmoves.push_back(move);
                    }
                }
            }
        }
    }
   bool result = matchfield->move(bestMove.from,bestMove.to);
}

std::vector<PossibleMove> Robot::findMoves(PossibleMove posMove,int heading){//heading:0,No,1,Left,2,Right,3,-Left,4,-Right
    std::vector<PossibleMove> moves;
        int nextX = posMove.to.x+1;
        int nextY = posMove.to.y+1;
    if(matchfield->field[posMove.to.x][posMove.to.y]->state){
        //Dame
        
        if(nextX<8&&nextY<8&&(heading==0||heading==1)){
            if(matchfield->field[nextX][nextY]==NULL){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
                moves.push_back(nextPosMove);
                for(PossibleMove move:findMoves(nextPosMove,1)){
                    moves.push_back(move);
                }
            }else if(!matchfield->field[nextX][nextY]->black){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
                for(PossibleMove move:findMoves(nextPosMove,1)){
                    moves.push_back(move);
                }
            } 
        }
        nextY = posMove.to.y-1;
        if(nextX<8&&nextY<8&&(heading==0||heading==2)){
            if(matchfield->field[nextX][nextY]==NULL){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
                moves.push_back(nextPosMove);
                for(PossibleMove move:findMoves(nextPosMove,2)){
                    moves.push_back(move);
                }
            }else if(!matchfield->field[nextX][nextY]->black){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
                for(PossibleMove move:findMoves(nextPosMove,2)){
                    moves.push_back(move);
                }
            } 
        }
        nextX = posMove.to.x-1;
        if(nextX<8&&nextY<8&&(heading==0||heading==3)){
            if(matchfield->field[nextX][nextY]==NULL){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
                moves.push_back(nextPosMove);
                for(PossibleMove move:findMoves(nextPosMove,3)){
                    moves.push_back(move);
                }
            }else if(!matchfield->field[nextX][nextY]->black){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
                for(PossibleMove move:findMoves(nextPosMove,3)){
                    moves.push_back(move);
                }
            } 
        }
        nextY = posMove.to.y+1;
        if(nextX<8&&nextY<8&&(heading==0||heading==4)){
            if(matchfield->field[nextX][nextY]==NULL){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
                moves.push_back(nextPosMove);
                for(PossibleMove move:findMoves(nextPosMove,4)){
                    moves.push_back(move);
                }
            }else if(!matchfield->field[nextX][nextY]->black){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
                for(PossibleMove move:findMoves(nextPosMove,4)){
                    moves.push_back(move);
                }
            } 
        }
    }else{
        //Normal
        if(nextX<8&&nextY<8&&heading!=2)
        if(matchfield->field[nextX][nextY]==NULL){
            PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
            moves.push_back(nextPosMove);
        }else if(!matchfield->field[nextX][nextY]->black){
            PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
            for(PossibleMove move:findMoves(nextPosMove,1)){
                moves.push_back(move);
            }
        } 
        nextY = posMove.to.y-1;
        if(nextX<8&&nextY>=0&&heading!=1)
        if(matchfield->field[nextX][nextY]==NULL){
            PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
            moves.push_back(nextPosMove);
        }else if(!matchfield->field[nextX][nextY]->black){
            PossibleMove nextPosMove(posMove.from,Coordinates(nextX,nextY),++(posMove.benefit));
            for(PossibleMove move:findMoves(nextPosMove,2)){
                moves.push_back(move);
            }
        } 
    }
    
    return moves;
}


#endif // ROBOT