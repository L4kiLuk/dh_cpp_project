#if !defined(HCONTROLLER)
#define HCONTROLLER

#include "Spielfeld.cpp"

class Controller
{
private:
    //gamefield
    Spielfeld* spielfeld;
    void render();
public:
    Controller(/* args */);
    ~Controller();
    void init();
    void newGame();
    void loadGame(std::string file);

};





#endif // HCONTROLLER
