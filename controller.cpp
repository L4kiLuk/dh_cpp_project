#if !defined(CONTROLLER)
#define CONTROLLER

#include <iostream>
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
                break;
            case '2':
                //Load Autosave
                std::cout << "Load Autosave"<< std::endl;
                break;
            default:
                std::cout <<"Bitte gib eine der oberen Möglichkeiten ein!"<<std::endl;
            
        }
    }
    //Handle manipulations(new Game||load Game||autosave)
    //Start the game

}

void Controller::render(){
    //Print the Game to cli
}

void Controller::newGame(){
    //create new Spielfeld
    //init it
    //start game
}

void Controller::loadGame(std::string file){
    //create new Spielfeld and init it from the file
    //start game
    
}

#endif // CONTROLLER
