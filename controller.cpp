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
                spielfeld = new Spielfeld;
                spielfeld->init();
                render();
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
