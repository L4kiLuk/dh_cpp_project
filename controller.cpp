#if !defined(CONTROLLER)
#define CONTROLLER

#include <iostream>
#include <regex>
#include "controller.hpp"
#include "messageCenter.cpp"



Controller::Controller(){
    
    
}

Controller::~Controller(){
    //Autosave the Game
}

void Controller::init(){
    //Print Welcome message
    std::cout << welcomeMessage();
    //Open the Input
    char inputCommand;
    while(1){
        std::cin >> inputCommand;
        //Handle the menu
        switch(inputCommand){
            case '1':
                //New Game
                std::cout << "New Game"<< std::endl;
                newGame();
                break;
            case '2':
                //Load Autosave
                std::cout << "Load Autosave"<< std::endl;
                break;
            default:
                std::cout <<"Bitte gib eine der oberen Möglichkeiten ein!"<<std::endl;
            
        }
    }
    

}

void Controller::render(){
    //Print the Game to cli
    //Simple implementation
    //For a clean Field a space for black a 0 and for white a 1
    system("clear");
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(spielfeld->feld[x][y]==NULL){
                std::cout <<"  ";
            }else if(spielfeld->feld[x][y]->schwarz){
                std::cout << "0 ";
            }else{
                std::cout <<"1 ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Player " << actualplayer << " is next!" << std::endl;
    std::cout << "move <fromx> <fromy> <tox> <toy>" << std::endl;
}

void Controller::newGame(){
    //create new Spielfeld
    spielfeld = new Spielfeld;
    //init it
    spielfeld->init();
    actualplayer = 0;
    //start game
    startGame();
}

void Controller::loadGame(std::string file){
    //create new Spielfeld and init it from the file
    //start game
    
}

void Controller::startGame(){
    bool isRunning = true;
    std::string nextMove;
    std::getline(std::cin,nextMove);
    render();
    while(isRunning){
        std::getline(std::cin,nextMove);
        std::regex move_pat("move [0-7] [0-7] [0-7] [0-7]");
        if(std::regex_match(nextMove,move_pat)){
            if(true /*spielfeld->move(Koordinaten_t(nextMove.at(5)-'0',nextMove.at(7)-'0'),Koordinaten_t(nextMove.at(9)-'0',nextMove.at(11)-'0'))*/){
                actualplayer=++actualplayer%2;
                render();
            }else{
            std::cout <<"Dieser Zug ist nicht Möglich" <<std::endl;
            }
        }else{
            std::cout << "Falscher Befehl!" << std::endl;
        }
        
    }
}

#endif // CONTROLLER
