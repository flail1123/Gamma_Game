# IPP
To use:
```
git clone git clone https://github.com/flail1123/Gamma_Game.git
cd Gamma_Game
cmake .
make
./gamma
```
now game settings in format "I \<width\> \<height\> \<players\> \<areas\>"<br>
  for example:
  ```
  I 20 20 2 2
  ```
to play:<br>
space: to take a field<br>
arrows: to move<br>
w: to use golden move<br>
c: to skip turn<br>
ctrl + d: to exit<br>

Description:

Gamma is a terminal based game that lets players occupy consecutive fields (fields that are next to each other form areas, their limit is set at the beginning of a game). <br>
Player that can't do a move loses. <br>
Once in a game player can use golden move that changes current field's ownership from opponent to current player (only if that won't create for this player new area that exceeds areas limit). <br>
