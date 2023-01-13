#if !defined(HCONTROLLER)
#define HCONTROLLER
#define AUTOSAVEFILE "autosave.sgf"
#define HIGHSCOREFILE "highscores.hsc"

#include "Matchfield.cpp"
#include "view.hpp"
#include <vector>
#include <chrono>
#include <ctime>
#include <csignal>

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
    void start();
    void newGame();
    void loadGame(std::string file);
    void saveGame(std::string file);
    void startGame();
    void saveHighscore(std::string playerName,int score);
    std::vector<Highscore> loadHighscores(); 
};
    void signal_handler(int signal);
    
#endif // HCONTROLLER
