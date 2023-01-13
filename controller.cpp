#if !defined(CONTROLLER)
#define CONTROLLER

#include <iostream>
#include <regex>
#include <fstream>
#include <thread>
#include <chrono>
#include "controller.hpp"
#include "view.cpp"
#include "robot.cpp"

//Constructor
Controller::Controller(){
    view = new View(&matchfield); 
}
//Deconstructor
Controller::~Controller(){
    //Autosave the Game
    delete view;
    delete matchfield;
}
//Start the controller 
void Controller::start(){
    //Init signalhandler
    sigObj=&matchfield;
    std::signal(SIGINT,signal_handler);
    view->printWelcomeMessage();
    //Look for autosave
    std::ifstream ifs(AUTOSAVEFILE);
    if(ifs.good()){
        ifs.close();
        view->printAutosaveFound();
        char input;
        std::cin>> input;
        if(input=='y'){
            loadGame(AUTOSAVEFILE);
        }
    }
    //Handle the menu
    char inputCommand;
    while(1){
        view->printMenu();
        std::cin >> inputCommand;
        //Handle the menu
        switch(inputCommand){
            case '1':   //New game
                newGame();
                break;
            case '2':   //Load savegame
                {view->printLine("Gib eine Datei an!");
                    std::string file;
                    std::cin >> file;
                    loadGame(file);}
                break;
            case '3': //Exit the Program
                exit(1);
                break;
            case '4':   //Show the highscores
                {view->printHighscore(loadHighscores());
                std::string s;
                std::getline(std::cin,s);
                std::getline(std::cin,s);}
                break;
            default:
                view->printLine("Bitte gib eine der oberen Möglichkeiten ein!");
            
        }
    }
    

}
//Starts a new game
void Controller::newGame(){
    matchfield = new Matchfield;
    matchfield->init();
    startGame();
}
//Load a game from a file and stats it
void Controller::loadGame(std::string file){
    std::ifstream ifs(file);
    matchfield = new Matchfield;
    char nextChar;
    ifs >> nextChar;
    matchfield->setActualPlayer(nextChar-'0');
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            ifs>>nextChar;
            if(nextChar!='#'){
                bool black = nextChar-'0';
                ifs>>nextChar;
                bool state = nextChar-'0';
                matchfield->field[x][y]= new Stone(state,black);
            }
        }
    }
    ifs.close();
    if(!file.compare(AUTOSAVEFILE)){
        std::remove(AUTOSAVEFILE);
    }
    startGame();
    
    
}
//Save a running game to a file
void Controller::saveGame(std::string file){
    std::ofstream ostream(file+".sgf");
    ostream<<(*Controller::sigObj)->getActualPlayer()<<std::endl;
    for(int column=0;column<8;column++){
        for(int row=0;row<8;row++){
            if((*Controller::sigObj)->field[column][row]==NULL){
                ostream<<"#";
            }else {
                ostream<<(*Controller::sigObj)->field[column][row]->black<<(*Controller::sigObj)->field[column][row]->state;
            }
        }
        ostream << std::endl;
    }
    ostream.close();
}
//Start the Game and handle while running
void Controller::startGame(){
    std::string inputString;
    char in;
    Robot robot = Robot(&matchfield);
    std::regex move_pat("move [a-h][1-8] [a-h][1-8]");
    std::regex hint_pat("hint [a-h][1-8]");
    std::regex help_pat("help");
    std::regex save_pat("save");
    std::regex exit_pat("exit");
    view->printLine("Möchtest du gegen den Computer Spielen? y/n");
    std::cin >> in;
    if(in='y'){
        withComputer=true;
    }
    std::getline(std::cin,inputString);//Clear the line
    matchfield->changeActualPlayer();//White begins
    view->render();
    while(1){
        std::getline(std::cin,inputString);
        if(std::regex_match(inputString,move_pat)){
            try{
                matchfield->move(Coordinates_t(7-(inputString.at(6)-'1'),inputString.at(5)-'a'),Coordinates_t(7-(inputString.at(9)-'1'),inputString.at(8)-'a'));
                view->render("Zug erfolgreich!");
                if(withComputer&&matchfield->getActualPlayer()==0){
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    robot.nextMove();
                    view->render("Zug erfolgreich!");
                }
            }catch(WrongMoveException ex){// Fehlerhafter Zug
                view->render(ex.info());
            }catch(GameEndException){//Spielende
                view->printVictory();
                std::cin >> in;
                if(in == 'y'){
                    view->printLine("Gib einen Namen ein!");
                    std::cin>>inputString;
                    saveHighscore(inputString,10);
                }
                break;
            }
        }
        else if(std::regex_match(inputString,hint_pat)){
            view->render("Das sind die Mögliche Züge!",matchfield->hint(Coordinates_t(7-(inputString.at(6)-'1'),inputString.at(5)-'a')));
        }
        else if (std::regex_match(inputString,help_pat)){
            view->printHelp();
        }
        else if (std::regex_match(inputString,save_pat)){
            view->printLine("Gibt einen Namen für die Datei ein:");
            std::getline(std::cin,inputString);
            saveGame(inputString);
            view->render("Gespeichert");
        }
        else if (std::regex_match(inputString,exit_pat)){
            break;
        }
        else{
            view->render("Falscher Befehl!");
        }
        
    }
    //Aufräumarbeiten
    delete matchfield;
}
//Save a new score to the high score file
void Controller::saveHighscore(std::string playerName,int score){
    std::ofstream ostream(HIGHSCOREFILE,std::ios::app);
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ostream << std::ctime(&time) <<" "<< playerName <<" "<<score <<std::endl;
    ostream.close();
}
//Retuns all entry's in the high score file
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
//Make a autosave if SIGINIT is raised
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
    ostream.close();
    std::exit(5);
}

#endif // CONTROLLER
