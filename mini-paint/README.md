# Mini-Paint v1

This is a basic drawing application that uses the SFML library to change pixels to a specific color.


## About SFML
SFML is the (S)imple (F)ast (M)edia (L)ibrary
It provides functionality for things such as 
creating a window, playing sounds, playing video,
and functionality for drawing graphics.

[link to website](https://www.sfml-dev.org/)


 ## Application Details 

* The window and drawable canvas is 600x400 pixels wide 

* Pressing the number keys 1 through 8 allows you to draw in a different color.
Use the Static Public Attributes of the sf::Color class such that:
** 1 = Black
** 2 = White
** 3 = Red
** 4 = Green
** 5 = Blue
** 6 = Yellow
** 7 = Magenta
** 8 = Cyan

* Pressing the space key will clear the canvas to the last color you have seleted.

* When a the mouse is pressed and a user left-clicks (i.e. on the pressed event, not 
released) a pixel color will change wherever the mouse is located. This should allow me to drag and draw over the canvas like a pencil on a piece of paper.

* Pressing the escape key should terminate the program.
 
 
 
 ## Compilation 
 
 Linux :
 
 [link]https://www.sfml-dev.org/tutorials/2.5/start-linux.php
 
 once you have dylibs in correct folder compile with 
 g++ with c++11 or greater
 
 * `g++ -std=c++11 mini-paint.cpp -o minipaint  -lsfml-graphics -lsfml-window -lsfml-system`
 
 and run with 
 * `./minipaint`
 
 Mac: 
 
 You can Run the code through xcode (or on terminal with above commands). Please see SFML documentation. 
 
 
