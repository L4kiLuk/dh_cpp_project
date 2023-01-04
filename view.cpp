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

#endif // VIEW
