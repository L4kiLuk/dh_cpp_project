# dh_cpp_project
The repository ofor the project from cpp. 
## Project Structure
Spielfeld
    + Feld[][]:Spielstein
    + move(from,to):bool
    + hint(from):Ziele[]
    + render()
    + save(File)
    + load(File)

Spielstein
    + Zustand:bool
    + Schwarz:bool
Controler
    + main():int
    + saveHighscore(NameSpieler)
    + loadHighscore():Highscores[] 
ComputerPlayer
 +nextmove()
 