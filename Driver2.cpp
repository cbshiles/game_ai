#include <stdio.h>

#include "MyGL.hpp"
#include "Mind.hpp"
#include "Screen.hpp"
#include "Game.hpp"
//#include "Brute.hpp"
#include "Human.hpp"

Player *a = new Human();
Player *b = new Player();
Game mainGame(a,b);

Screen* s;

void mouseInput(int button, int state, int x, int y){
  s -> mouseInput(button, state, x, y);
}

void drawScene(){
   s -> drawScene();
}

void resize(int x, int y){
  s -> resize(x,y);
}

void set_callbacks(){
  glutMouseFunc(mouseInput);
    
  glutDisplayFunc(drawScene); 
   
  glutReshapeFunc(resize);
}


void call_game(int x, int y){
  mainGame.request_move(x,y);
}

int main(int argc, char* argv[]){
  if (mainGame.areHumans())
    mainGame.loadScreen(new Screen(900, 900));
  mainGame.play_game();
}
