#if !defined(HCONTROLLER)
#define HCONTROLLER

#include "Spielfeld.cpp"
#include "view.hpp"

class Controller
{
private:
    View* view;
    Spielfeld* spielfeld;
public:
    Controller(/* args */);
    ~Controller();
    void init();
    void newGame();
    void loadGame(std::string file);
    void startGame();

};





#endif // HCONTROLLER
