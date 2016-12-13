#include "Human.hpp"

Player *a = new Human();
Player *b = new Brute();
Game mainGame(a,b);
Screen *s;

void mouseInput(int button, int state, int x, int y){
  if (!button && state==1)
    mainGame.request_move(x, y);
}

void drawScene(){
   s -> draw();
}

void resize(int x, int y){
  s -> dims(x,y);
}

int main(int argc, char* argv[]){
  if (mainGame.areHumans()){
    s = new Screen(SQR*X, SQR*Y, GAME);
    mainGame.loadScreen(s);
  }
  mainGame.play_game();
}
