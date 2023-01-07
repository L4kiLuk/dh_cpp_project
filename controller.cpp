#if !defined(CONTROLLER)
#define CONTROLLER

#include <iostream>
#include <regex>
#include <fstream>
#include "controller.hpp"
#include "messageCenter.cpp"
#include "view.cpp"


Controller::Controller(){
    view = new View(&matchfield);
    
}

Controller::~Controller(){
    //Autosave the Game
    std::cout << "Bye Bye" << std::endl;
    delete view;
}

void Controller::init(){
    sigObj=&matchfield;
    std::signal(SIGINT,signal_handler);
    //Print Welcome message
    std::cout << welcomeMessage();
    std::ifstream ifs("autosave.asv");
    if(ifs.good()){
        ifs.close();
        std::cout<<"Es wurde ein Autospeicherstand gefunden. Möchtest du ihn laden? y/n"<<std::endl;
        char input;
        std::cin>> input;
        if(input=='y'){
            loadGame("autosave.asv");
            std::remove("autosave.asv");
            startGame();
        }
    }
    //Open the Input
    std::cout<< "1: Beginne neues Spiel."<<std::endl<<"2: Lade gespeichertes Spiel."<<std::endl<<"3: Verlasse das Programm."<<std::endl;
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
            case '3':
                exit(1);
                break;
            default:
                std::cout <<"Bitte gib eine der oberen Möglichkeiten ein!"<<std::endl;
            
        }
    }
    

}

void Controller::newGame(){
    //create new Spielfeld
    matchfield = new Matchfield;
    //init it
    matchfield->init();
    //start game
    startGame();
}

void Controller::loadGame(std::string file){
    std::ifstream ifs(file);
    matchfield = new Matchfield;
    char nextchar;
    ifs >> nextchar;
    matchfield->setActualPlayer(nextchar-'0');
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            ifs>>nextchar;
            if(nextchar!='#'){
                bool black = nextchar-'0';
                ifs>>nextchar;
                bool state = nextchar-'0';
                matchfield->field[x][y]= new Stone(state,black);
            }
        }
    }
    
    
}

void Controller::startGame(){
    bool isRunning = true;
    std::string nextMove;
    std::getline(std::cin,nextMove);
    view->render();
    while(isRunning){
        std::getline(std::cin,nextMove);
        std::regex move_pat("move [0-7] [0-7] [0-7] [0-7]");
        std::regex hint_pat("hint [0-7] [0-7]");
        if(std::regex_match(nextMove,move_pat)){
            if(true /*spielfeld->move(Coordinates_t(nextMove.at(5)-'0',nextMove.at(7)-'0'),Coordinates_t(nextMove.at(9)-'0',nextMove.at(11)-'0'))*/){
                matchfield->changeActualPlayer(); //Ausbauen sobald in move() gewechselt wird.
                view->render("Zug erfolgreich!");
            }else{
                view->render("Dieser Zug ist nicht Möglich");
            }
        }
        else if(std::regex_match(nextMove,hint_pat)){
            //matchfield->hint(Coordinates_t(nextMove.at(5)-'0',nextMove.at(7)-'0'));
            view->render("Das sind die Mögliche Züge!");
        }
        else{
            view->render("Falscher Befehl!");
        }
        
    }
}

void Controller::saveHighscore(std::string playerName,int score){
    std::ofstream ostream("highscores.hsc",std::ios::app);
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ostream << std::ctime(&time) <<" "<< playerName <<" "<<score <<std::endl;
    ostream.close();
}

std::vector<Highscore> Controller::loadHighscores(){
    std::vector<Highscore> highscores;
    std::ifstream istream("highscores.hsc");
    std::string name;
    std::string time;
    int score;
    while (std::getline(istream,time))
    {
        istream >> name;
        istream >> score;
        highscores.push_back(Highscore(name,score,time));
        std::getline(istream,time); //to jump to next line and read the date right.
    }
    istream.close();
    return highscores;
}

void signal_handler(int signal){
    std::ofstream ostream("autosave.asv");
    ostream<<(*Controller::sigObj)->getActualPlayer()<<std::endl;
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if((*Controller::sigObj)->field[x][y]==NULL){
                ostream<<"#";
            }else {
                ostream<<(*Controller::sigObj)->field[x][y]->black<<(*Controller::sigObj)->field[x][y]->state;
            }
        }
        ostream << std::endl;
    }
    std::cout <<"Naja der hellste bist du jetzt wohl nicht!" << std::endl;
    std::exit(5);
}

#endif // CONTROLLER
