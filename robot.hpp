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
public:
    Robot(Matchfield** pMatchfield){matchfield = (*pMatchfield);}
    void nextMove();    //Makes the best move for the Robot.
    std::vector<PossibleMove> findMoves(PossibleMove from,int heading);
};

#endif // HROBOT