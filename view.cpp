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
    CLEARCONSOLE
    std::cout << " a b c d e f g h"<<std::endl;
    for(int column=0;column<8;column++){
        std::cout << 8-column;
        for(int row=0;row<8;row++){
            bool aHintPrinted = false;
            for(Coordinates coord:hints){
                if(coord.x==column&&coord.y==row){
                    std::cout <<HINTSTONE;
                    aHintPrinted=true;
                    break;
                }
            }
            if(aHintPrinted){
                continue;
            }
            if((*gamefield)->field[column][row]==NULL){
                if((column+row)%2){
                    std::cout <<EMPTYBLACKFIELD; 
                }else{
                    std::cout <<EMPTYWHITEFIELD;
                }
                continue;
            }
            if((*gamefield)->field[column][row]->black){
                if((*gamefield)->field[column][row]->state){
                    std::cout << BLACKDAME;
                }else{
                    std::cout <<BLACKSTONE;
                }
                continue;
            }
            if(!(*gamefield)->field[column][row]->black){
                if((*gamefield)->field[column][row]->state){
                    std::cout << WHITEDAME;
                }else{
                    std::cout <<WHITESTONE;
                }
                continue;
            }
        }
        std::cout <<8-column<< std::endl;
    }
    std::cout << " a b c d e f g h"<<std::endl;
}
//Prints the welcome message
void View::printWelcomeMessage(){
    std::cout << "Willkommen zu Dame. \n Wir freuen uns, dass du unser Spiel spielen willst. \n Während des Spiels kannst du mit help die Hilfe ansehen\n";
}
//Prints the help
void View::printHelp(){
    std::cout   << "help" << std::endl
                << "    Zeige diese Hilfe an." << std::endl
                << "move <fromCol><fromRow> <toCol><toRow> (move a3 b4)" << std::endl
                << "    Ziehe einen Stein an eine andere Position." << std::endl
                << "hint <fromCol><fromRow>" << std::endl
                << "    Lass dir die Möglichen Zuge eines Steines anzeigen" << std::endl
                << "save" << std::endl
                << "    Speichere den aktuellen Spielstand in eine Datei" << std::endl
                << "exit" << std::endl
                << "    Gehe zu Menü ohne zu speichern" << std::endl
                << "Sollte es Probleme bei der Darstellung des Spielfeldes geben, dann passe bitte die Datei view.hpp an."<<std::endl;
}
//Prints the menu
void View::printMenu(){
    CLEARCONSOLE
    printWelcomeMessage();
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
    << "Es wurden "<<(*gamefield)->moves<< "Züge gebraucht. Möchtest du einen Highscoreeintrag? y/n"<<std::endl;
}
//Prints the field without anything else
void View::printField(){
    std::cout << " a b c d e f g h"<<std::endl;
    for(int column=0;column<8;column++){
        std::cout << 8-column;
        for(int row=0;row<8;row++){
            if((*gamefield)->field[column][row]==NULL){
                if((column+row)%2){
                    std::cout <<EMPTYBLACKFIELD; 
                }else{
                    std::cout <<EMPTYWHITEFIELD;
                }
                continue;
            }
            if((*gamefield)->field[column][row]->black){
                if((*gamefield)->field[column][row]->state){
                    std::cout << BLACKDAME;
                }else{
                    std::cout <<BLACKSTONE;
                }
                continue;
            }
            if(!(*gamefield)->field[column][row]->black){
                if((*gamefield)->field[column][row]->state){
                    std::cout << WHITEDAME;
                }else{
                    std::cout <<WHITESTONE;
                }
                continue;
            }
        }
        std::cout <<8-column<< std::endl;
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