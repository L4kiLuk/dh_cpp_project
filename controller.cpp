#if !defined(CONTROLLER)
#define CONTROLLER

#include <iostream>
#include <regex>
#include <fstream>
#include "controller.hpp"
#include "view.cpp"
#include "robot.cpp"

Controller::Controller(){
    view = new View(&matchfield);
    
}

Controller::~Controller(){
    //Autosave the Game
    delete view;
    delete matchfield;
}

void Controller::init(){
    sigObj=&matchfield;
    std::signal(SIGINT,signal_handler);
    //Print Welcome message
    view->printWelcomeMessage();
    std::ifstream ifs(AUTOSAVEFILE);
    if(ifs.good()){
        ifs.close();
        view->printAutosaveFound();
        char input;
        std::cin>> input;
        if(input=='y'){
            loadGame(AUTOSAVEFILE);
            std::remove(AUTOSAVEFILE);
            startGame();
        }
    }
    //Open the Input
    view->printMenu();
    char inputCommand;
    while(1){
        std::cin >> inputCommand;
        //Handle the menu
        switch(inputCommand){
            case '1':
                //New Game
                newGame();
                break;
            case '2':
                //Load Autosave
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
    std::cout << "Möchtest du gegen den Computer Spielen? y/n"<<std::endl;
    char in;
    std::cin >> in;
    if(in='y'){
        withComputer=true;
    }
    bool isRunning = true;
    std::string nextMove;
    std::getline(std::cin,nextMove);
    Robot robot = Robot(&matchfield);
    matchfield->changeActualPlayer();
    view->render();
    while(isRunning){
        std::getline(std::cin,nextMove);
        std::regex move_pat("move [a-h][1-8] [a-h][1-8]");
        std::regex hint_pat("hint [a-h][1-8]");
        std::regex help_pat("help");
        if(std::regex_match(nextMove,move_pat)){
            try{
                matchfield->move(Coordinates_t(7-(nextMove.at(6)-'1'),nextMove.at(5)-'a'),Coordinates_t(7-(nextMove.at(9)-'1'),nextMove.at(8)-'a'));
                view->render("Zug erfolgreich!");
                if(withComputer&&matchfield->getActualPlayer()==0){
                    robot.nextMove();
                    view->render();
                }
            }catch(WrongMoveException ex){// Fehlerhafter Zug
                view->render(ex.info());
            }catch(GameEndException){//Spielende
                view->printVictory();
            }
        }
        else if(std::regex_match(nextMove,hint_pat)){
            view->render("Das sind die Mögliche Züge!",matchfield->hint(Coordinates_t(nextMove.at(6)-'1',nextMove.at(5)-'a')));
        }
        else if (std::regex_match(nextMove,help_pat)){
            view->printHelp();
        }        
        else{
            view->render("Falscher Befehl!");
        }
        
    }
}

void Controller::saveHighscore(std::string playerName,int score){
    std::ofstream ostream(HIGHSCOREFILE,std::ios::app);
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ostream << std::ctime(&time) <<" "<< playerName <<" "<<score <<std::endl;
    ostream.close();
}

std::vector<Highscore> Controller::loadHighscores(){
    std::vector<Highscore> highscores;
    std::ifstream istream(HIGHSCOREFILE);
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
    std::ofstream ostream(AUTOSAVEFILE);
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
    std::exit(5);
}

#endif // CONTROLLER
