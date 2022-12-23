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
    std::string inputCommand;
    while(1){
        std::cin >> inputCommand;
        //Handle the Menu
    }
    //Handle manipulations(new Game||load Game||autosave)
    //Start the game

}

void Controller::render(){
    //Print the Game to cli
}


#endif // CONTROLLER
