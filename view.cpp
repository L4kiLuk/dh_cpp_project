#if !defined(VIEW)
#define VIEW

#include "view.hpp"

void View::render(){
    CLEARCONSOLE
    std::cout << "Spieler " << (*gamefield)->getActualPlayer()<< " ist an der Reihe!" <<std::endl;
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if((*gamefield)->field[x][y]==NULL){
                if((x+y)%2){
                    std::cout <<EMPTYBLACKFIELD; 
                }else{
                    std::cout <<EMPTYWHITEFIELD;
                }
            }else if((*gamefield)->field[x][y]->black){
                std::cout << BLACKSTONE;
            }else{
                std::cout <<WHITESTONE;
            }
        }
        std::cout << std::endl;
    }
    std::cout << optmessage << std::endl;
    optmessage = "";
}

void View::render(std::string message){
    optmessage = message;
    render();
}

void View::printWelcomeMessage(){
    std::cout << "Willkommen zu Dame. \n Wir freuen uns, dass du unser Spiel spielen willst. \n Wenn du Hilfe brauchst, schreibe einfach \"help\".\n";
}

void View::printHelp(){
    std::cout   << "help" << std::endl
                << "    Zeige diese Hilfe an." << std::endl
                << "move <fromx> <fromy> <tox> <toy>" << std::endl
                << "    Ziehe einen Stein an eine andere Position." << std::endl
                << "hint <fromx> <fromy>" << std::endl
                << "    Lass dir die Möglichen Zuge eines Steines anzeigen" << std::endl;
}

void View::printMenu(){
    std::cout<< "1: Beginne neues Spiel."<<std::endl<<"2: Lade gespeichertes Spiel."<<std::endl<<"3: Verlasse das Programm."<<std::endl;
}

void View::printAutosaveFound(){
    std::cout<<"Es wurde ein Autospeicherstand gefunden. Möchtest du ihn laden? y/n"<<std::endl;
}

#endif // VIEW
