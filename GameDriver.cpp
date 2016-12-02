#include <stdio.h>
#include "MyGL.hpp"
#include "TicTac.hpp"

Player *a = new Player();
Player *b = new Brute();
Game mainGame(a,b);

// void mouseInput(int button, int state, int x, int y){
//   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
//     mainGame.request_move(x, y);
//   }
// }

int main(int argc, char* argv[]){ int i;
   printf("Winner: %d\n", mainGame.play_game());

  //  glutMouseFunc(mouseInput);
  
  //loop(i, argc){printf("%s\n", argv[i]);}
}
