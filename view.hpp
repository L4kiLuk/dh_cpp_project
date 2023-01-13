#if !defined(VIEWH)
#define VIEWH
#define USEUNICODE

#ifdef USEUNICODE
#define CLEARCONSOLE std::cout<< u8"\033[2J\033[1;1H";
#define EMPTYBLACKFIELD "\033[40m  \033[0m"
#define EMPTYWHITEFIELD "\033[47m  \033[0m"
#define BLACKSTONE "\033[40;31mⓄ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#define WHITESTONE "\033[40;37mⓄ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#define BLACKDAME "\033[40;31mⒹ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#define WHITEDAME "\033[40;37mⒹ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#define HINTSTONE "\033[40;35mⓄ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#else
#define CLEARCONSOLE 
#define EMPTYBLACKFIELD "  "
#define EMPTYWHITEFIELD "  "
#define BLACKSTONE "0 "
#define WHITESTONE "1 "
#define BLACKDAME "00" 
#define WHITEDAME "11" 
#define HINTSTONE "00" 
#endif

#include <iostream>
#include "Matchfield.cpp"

typedef struct s_highscore
{
    int score;
    std::string name;
    std::string time;
    s_highscore(std::string playerName, int score,std::string time):score(score),name(playerName),time(time){}
}Highscore;

//Handle all Output while a Game is running
class View
{
private:
    /* data */
    Matchfield** gamefield;

public:
    View(Matchfield** ptr_gamefield): gamefield(ptr_gamefield){};
    void render();
    void render(std::string message);
    void render(std::string message, std::vector<Coordinates> hints);
    void printWelcomeMessage();
    void printHelp();
    void printMenu();
    void printAutosaveFound();
    void printVictory();
    void printField();
    void printHighscore(std::vector<Highscore> highscores);
    void printLine(std::string line);
    
};

#endif // VIEWH