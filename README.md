# dh_cpp_project
The repository for the project from cpp. 
## Project Structure
Spielfeld
    + Feld[][]:Spielstein - Pascal
    + move(from,to):bool - Pascal
    + hint(from):Ziele[] - Pascal

Spielstein - Pascal
    + Zustand:bool
    + Schwarz:bool
    + 
Controler
    + saveHighscore(NameSpieler) - Lukas
    + loadHighscore():Highscores[] - Lukas
    + save(File) - Lukas
    + load(File) - Lukas
    + render() - Lukas
    + 
ComputerPlayer
    + nextmove()
 
 Main
    + main():int - Lukas

# ToDo
- refactor to Englisch
- Dateinamen anpassen
- actualPlayer in Spielfeld einbauen
- zugcounter in Spieldeld einbauen
- Gewinner entscheidung über isrunning, exeption, ...
- isrunning:bool in Spielfeld einbauen
- Hintsystem vorbereiten
- Schfaledzeichen kontrolieren