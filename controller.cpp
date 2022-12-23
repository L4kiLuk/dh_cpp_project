#if !defined(CONTROLLER)
#define CONTROLLER

#include <iostream>
#include "controller.hpp"
#include "messageCenter.cpp"

//Constructor: Init the default game
Controller::Controller(){
    
    
}

Controller::~Controller(){
    //Autosave the Game
}

void Controller::start(){
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


#endif // CONTROLLER
