#if !defined(HROBOT)
#define HROBOT


#include "Matchfield.cpp"
#include <vector>

typedef struct s_possibleMove
{
    Coordinates from;
    Coordinates to;
    int benefit=-1;
    s_possibleMove(Coordinates from, Coordinates to):from(from),to(to){};
    s_possibleMove(Coordinates from, Coordinates to,int benefit):from(from),to(to),benefit(benefit){};
}PossibleMove;


class Robot
{
private:
    /* data */
    Matchfield* matchfield;
    PossibleMove bestMove=PossibleMove(Coordinates(0,0),Coordinates(0,0));
public:
    Robot(Matchfield** pMatchfield){matchfield = (*pMatchfield);}
    void nextMove();    //Makes the best move for the Robot.
    int evaluateMove(Coordinates from, Coordinates to); //returns a nubmer based on how good a move is.
    std::vector<PossibleMove> findMoves(Coordinates from);

};





#endif // HROBOT