#if !defined(ROBOT)
#define ROBOT

#include "robot.hpp"

//Do the best possible move
void Robot::nextMove(){
    std::vector<PossibleMove> possmoves;
    PossibleMove bestMove=PossibleMove(Coordinates(0,0),Coordinates(0,0));
    for(int column=0;column<8;column++){
        for(int row=0;row<8;row++){
            if(matchfield->field[column][row]!=NULL){
                if(matchfield->field[column][row]->black){
                    std::vector<PossibleMove> moves = findMoves(PossibleMove(Coordinates(column,row),Coordinates(column,row),-1),0);
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
//Find all possible moves for a stone
std::vector<PossibleMove> Robot::findMoves(PossibleMove posMove,int heading){
    std::vector<PossibleMove> moves;
        int nextColumn = posMove.to.x+1;
        int nextRow = posMove.to.y+1;
    if(matchfield->field[posMove.to.x][posMove.to.y]->state){
        if(nextColumn<8&&nextRow<8&&(heading==0||heading==1)){
            if(matchfield->field[nextColumn][nextRow]==NULL){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
                moves.push_back(nextPosMove);
                for(PossibleMove move:findMoves(nextPosMove,1)){
                    moves.push_back(move);
                }
            }else if(!matchfield->field[nextColumn][nextRow]->black){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
                for(PossibleMove move:findMoves(nextPosMove,1)){
                    moves.push_back(move);
                }
            } 
        }
        nextRow = posMove.to.y-1;
        if(nextColumn<8&&nextRow<8&&(heading==0||heading==2)){
            if(matchfield->field[nextColumn][nextRow]==NULL){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
                moves.push_back(nextPosMove);
                for(PossibleMove move:findMoves(nextPosMove,2)){
                    moves.push_back(move);
                }
            }else if(!matchfield->field[nextColumn][nextRow]->black){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
                for(PossibleMove move:findMoves(nextPosMove,2)){
                    moves.push_back(move);
                }
            } 
        }
        nextColumn = posMove.to.x-1;
        if(nextColumn<8&&nextRow<8&&(heading==0||heading==3)){
            if(matchfield->field[nextColumn][nextRow]==NULL){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
                moves.push_back(nextPosMove);
                for(PossibleMove move:findMoves(nextPosMove,3)){
                    moves.push_back(move);
                }
            }else if(!matchfield->field[nextColumn][nextRow]->black){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
                for(PossibleMove move:findMoves(nextPosMove,3)){
                    moves.push_back(move);
                }
            } 
        }
        nextRow = posMove.to.y+1;
        if(nextColumn<8&&nextRow<8&&(heading==0||heading==4)){
            if(matchfield->field[nextColumn][nextRow]==NULL){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
                moves.push_back(nextPosMove);
                for(PossibleMove move:findMoves(nextPosMove,4)){
                    moves.push_back(move);
                }
            }else if(!matchfield->field[nextColumn][nextRow]->black){
                PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
                for(PossibleMove move:findMoves(nextPosMove,4)){
                    moves.push_back(move);
                }
            } 
        }
    }else{
        //Normal
        if(nextColumn<8&&nextRow<8&&heading!=2)
        if(matchfield->field[nextColumn][nextRow]==NULL){
            PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
            moves.push_back(nextPosMove);
        }else if(!matchfield->field[nextColumn][nextRow]->black){
            PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
            for(PossibleMove move:findMoves(nextPosMove,1)){
                moves.push_back(move);
            }
        } 
        nextRow = posMove.to.y-1;
        if(nextColumn<8&&nextRow>=0&&heading!=1)
        if(matchfield->field[nextColumn][nextRow]==NULL){
            PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
            moves.push_back(nextPosMove);
        }else if(!matchfield->field[nextColumn][nextRow]->black){
            PossibleMove nextPosMove(posMove.from,Coordinates(nextColumn,nextRow),++(posMove.benefit));
            for(PossibleMove move:findMoves(nextPosMove,2)){
                moves.push_back(move);
            }
        } 
    }
    return moves;
}


#endif // ROBOT