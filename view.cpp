#if !defined(VIEW)
#define VIEW

#include "view.hpp"
//Print the field
void View::render(){
    render("");
}
//Print the field and additional information
void View::render(std::string message){
    CLEARCONSOLE
    std::cout << "Spieler " << (*gamefield)->getActualPlayer()<< " ist an der Reihe!" <<std::endl;
    printField();
    std::cout << message << std::endl;
}
//Print the field including hint stones
void View::render(std::string message, std::vector<Coordinates> hints){
    std::cout << " a b c d e f g h"<<std::endl;
    for(int column=0;column<8;column++){
        std::cout << 8-column;
        for(int row=0;row<8;row++){
            for(Coordinates coord:hints){
                if(coord.x==column&&coord.y==row){
                    std::cout <<EMPTYBLACKFIELD;
                    continue;
                }
            }
            if((*gamefield)->field[column][row]==NULL){
                if((column+row)%2){
                    std::cout <<EMPTYBLACKFIELD; 
                }else{
                    std::cout <<EMPTYWHITEFIELD;
                }
            }else if((*gamefield)->field[column][row]->black){
                if((*gamefield)->field[column][row]->state){
                    std::cout << BLACKDAME;
                }else{
                    std::cout <<BLACKSTONE;
                }
            }else{
                if((*gamefield)->field[column][row]->state){
                    std::cout << WHITEDAME;
                }else{
                    std::cout <<WHITESTONE;
                }
            }
        }
        std::cout <<8-column<< std::endl;
    }
    std::cout << " a b c d e f g h"<<std::endl;
}
//Prints the welcome message
void View::printWelcomeMessage(){
    std::cout << "Willkommen zu Dame. \n Wir freuen uns, dass du unser Spiel spielen willst. \n Wenn du Hilfe brauchst, schreibe einfach \"help\".\n";
}
//Prints the help
void View::printHelp(){
    std::cout   << "help" << std::endl
                << "    Zeige diese Hilfe an." << std::endl
                << "move <fromx><fromy> <tox><toy> (move a3 b4)" << std::endl
                << "    Ziehe einen Stein an eine andere Position." << std::endl
                << "hint <fromx><fromy>" << std::endl
                << "    Lass dir die Möglichen Zuge eines Steines anzeigen" << std::endl
                << "Sollte es Probleme bei der Darstellung des Spielfeldes geben, dann passe bitte die Datei view.hpp an."<<std::endl;
}
//Prints the menu
void View::printMenu(){
    CLEARCONSOLE
    std::cout<< "Menü:"<<std::endl<<"1: Beginne neues Spiel."<<std::endl<<"2: Lade gespeichertes Spiel."<<std::endl<<"3: Verlasse das Programm."<<std::endl<<"4: Zeige die Highscores an."<<std::endl;
}
//Prints autosave found message
void View::printAutosaveFound(){
    std::cout<<"Es wurde ein Autospeicherstand gefunden. Möchtest du ihn laden? y/n"<<std::endl;
}
//Print the victory scene
void View::printVictory(){
    CLEARCONSOLE
    std::cout << "Das Spiel ist entschieden!"<<std::endl;
    printField();
    std::cout << "Spieler " << (*gamefield)->getActualPlayer()<< " hat gewonnen!" <<std::endl
    << "Es wurden "<< "Züge gebraucht. Möchtest du einen Highscoreeintrag? y/n"<<std::endl;
}
//Prints the field without anything else
void View::printField(){
    std::cout << " a b c d e f g h"<<std::endl;
    for(int x=0;x<8;x++){
        std::cout << 8-x;
        for(int y=0;y<8;y++){
            if((*gamefield)->field[x][y]==NULL){
                if((x+y)%2){
                    std::cout <<EMPTYBLACKFIELD; 
                }else{
                    std::cout <<EMPTYWHITEFIELD;
                }
            }else if((*gamefield)->field[x][y]->black){
                if((*gamefield)->field[x][y]->state){
                    std::cout << BLACKDAME;
                }else{
                    std::cout <<BLACKSTONE;
                }
            }else{
                if((*gamefield)->field[x][y]->state){
                    std::cout << WHITEDAME;
                }else{
                    std::cout <<WHITESTONE;
                }
            }
        }
        std::cout <<8-x<< std::endl;
    }
    std::cout << " a b c d e f g h"<<std::endl;
}
//Prints the high score table
void View::printHighscore(std::vector<Highscore> highscores){
    CLEARCONSOLE
    for(Highscore highscore:highscores){
        std::cout << highscore.time <<"  "<< highscore.score<< "   " << highscore.name<< std::endl;
    }
}
//Prints a single Line of Text
void View::printLine(std::string line){
    std::cout<<line<<std::endl;
}

#endif // VIEW