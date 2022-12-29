#if !defined(HCONTROLLER)
#define HCONTROLLER

#include "Spielfeld.cpp"
#include "view.hpp"
#include <vector>
#include <chrono>
#include <ctime>

typedef struct s_highscore
{
    int score;
    std::string name;
    std::string time;
    s_highscore(std::string playerName, int score,std::string time):score(score),name(playerName),time(time){}
}Highscore;

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
    void saveHighscore(std::string playerName,int score);
    std::vector<Highscore> loadHighscores();

};







#endif // HCONTROLLER
