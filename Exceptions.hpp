#include <iostream>


class WrongMoveException : public std::exception{
    public:
    char * info(){
        return "Move nicht möglich";
    }
};

class GameEndException : public std::exception{
    public:
    char * info(){
        return "Spiel beendet";
    }
};

