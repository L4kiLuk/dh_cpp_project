#if !defined(HCONTROLLER)
#define HCONTROLLER

#include "Matchfield.cpp"
#include "view.hpp"
#include <vector>
#include <chrono>
#include <ctime>
#include <csignal>

#define AUTOSAVEFILE "autosave.sgf"
#define HIGHSCOREFILE "highscores.hsc"

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
    Matchfield* matchfield;
    bool withComputer = false;
public:
    static inline Matchfield** sigObj;
    Controller(/* args */);
    ~Controller();
    void init();
    void newGame();
    void loadGame(std::string file);
    void startGame();
    void saveHighscore(std::string playerName,int score);
    std::vector<Highscore> loadHighscores();
    
};
    void signal_handler(int signal);







#endif // HCONTROLLER
