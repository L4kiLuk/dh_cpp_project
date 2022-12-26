#if !defined(HCONTROLLER)
#define HCONTROLLER

#include "Spielfeld.cpp"

class Controller
{
private:
    //gamefield
    Spielfeld* spielfeld;
    int actualplayer; //1 is the Computer
    void render();
public:
    Controller(/* args */);
    ~Controller();
    void init();
    void newGame();
    void loadGame(std::string file);
    void startGame();

};





#endif // HCONTROLLER
