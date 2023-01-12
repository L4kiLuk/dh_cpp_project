#if !defined(VIEWH)
#define VIEWH
#define USEUNICODE

#ifdef USEUNICODE
#define CLEARCONSOLE std::cout<< u8"\033[2J\033[1;1H";
#define EMPTYBLACKFIELD "\033[40m  \033[0m"
#define EMPTYWHITEFIELD "\033[47m  \033[0m"
#define BLACKSTONE "\033[40;31m⭗ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#define WHITESTONE "\033[40;37m⭗ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#define BLACKDAME "\033[40;31mⒹ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#define WHITEDAME "\033[40;37mⒹ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
#define HINTSTONE "\033[40;35m⭗ \033[0m" //Zeichen gerne auswechseln, sollte es nicht schön angezeigt werden
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
/*
  0   0   0   0 
0   0   0   0   
  0   0   0   0 
                
                
1   1   1   1   
  1   1   1   1 
1   1   1   1   
⎡      ⎤
⎢      ⎥
⎣      ⎦
*/

#include <iostream>
#include "Matchfield.cpp"
//Handle all Output while a Game is running
class View
{
private:
    /* data */
    std::string optmessage;
    Matchfield** gamefield;

    
public:
    View(Matchfield** ptr_gamefield): gamefield(ptr_gamefield){};
    void render();
    void render(std::string message);
    void setOptMessage(std::string message){optmessage=message;} //Set a message to print at the next rendering. Message will be deleted after the next call of render()
    void printWelcomeMessage();
    void printHelp();
    void printMenu();
    void printAutosaveFound();
    void printVictory();
    void printField();
    
};



#endif // VIEWH