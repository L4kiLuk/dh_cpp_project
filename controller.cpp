#if !defined(CONTROLLER)
#define CONTROLLER

#include <iostream>
#include <regex>
#include "controller.hpp"
#include "messageCenter.cpp"
#include "view.cpp"

Controller::Controller(){
    view = new View(&spielfeld);
    
}

Controller::~Controller(){
    //Autosave the Game
    delete view;
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

void Controller::newGame(){
    //create new Spielfeld
    spielfeld = new Spielfeld;
    //init it
    spielfeld->init();
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
    view->render();
    while(isRunning){
        std::getline(std::cin,nextMove);
        std::regex move_pat("move [0-7] [0-7] [0-7] [0-7]");
        if(std::regex_match(nextMove,move_pat)){
            if(true /*spielfeld->move(Koordinaten_t(nextMove.at(5)-'0',nextMove.at(7)-'0'),Koordinaten_t(nextMove.at(9)-'0',nextMove.at(11)-'0'))*/){
                spielfeld->changeActualPlayer();
                view->render("Zug erfolgreich!");
            }else{
                view->render("Dieser Zug ist nicht Möglich");
            }
        }else{
            view->render("Falscher Befehl!");
        }
        
    }
}

#endif // CONTROLLER
