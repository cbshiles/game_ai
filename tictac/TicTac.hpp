#define X 3
#define Y 3
#define SQR 275 //1 dimension of a square
#define GAME "Tic-Tac-Toe"

#include "../Core.hpp"

#define check if (vert[0] && vert[0]==vert[1] && vert[0]==vert[2]) return vert[0];

  //returns a players# if winner, 0 for tie, -1 for unfinished
char Mind::check_outcome(){int i,j,k,s,add; 
  char vert[3]; //the 3 vertices in a row
  char full=1;
    loop(i,2){
      loop(j,3){loop(k,3){
	  if (i) {
	    vert[k] = board[j][k];
	    if (! vert[k]) full=0;
	  }
	  else vert[k] = board[k][j];
	}check}
      
      if (i) s=0, add=1;
      else s=2, add=-1;
      loop(j,3){
	vert[j] = board[j][s];
	s += add;}
      check}
    return full?0:-1;
  }

char Game::place(int x, int y){
    char* spot = &board[x][y];
    if (! *spot){
      *spot = cplayer();
      return (valid=1);}
    return 0;
  }

void Player::move(){int i,j;
  loop(i, Y){
    loop(j, X){
      if(! board[j][i]) { g->place(j,i); return; }
    }}
}

void Screen::init(){
  glLineWidth(3);
  black->setBackground();
  white->set();
}

float min(int z){return -.9 + z*2.0/3;}

float max(int z){return -.433 + z*2.0/3;} 
  
void drawShape(int x, int y, char board[][Y]){

  char shape = board[x][y];
  y = 2-y; //# mehh
  if (shape == 1){//draw x
    glBegin(GL_LINES);
    glVertex3f(min(x),min(y),0);
    glVertex3f(max(x),max(y),0);

    glVertex3f(min(x),max(y),0);
    glVertex3f(max(x),min(y),0);
    
    glEnd();
  } else if (shape == 2) { //draw o
    glBegin(GL_LINE_STRIP);
    glVertex3f(min(x),min(y),0);
    glVertex3f(min(x),max(y),0);
    glVertex3f(max(x),max(y),0);
    glVertex3f(max(x),min(y),0);
    glVertex3f(min(x),min(y),0);
    glEnd();
  }
}

void Screen::draw(){
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)


  float ix = 1.0/3, iy = 1.0/3;
  glBegin(GL_LINES);
  white->set();

  glVertex3f(-ix, -1, 0);
  glVertex3f(-ix, 1, 0);

  glVertex3f(ix, -1, 0);
  glVertex3f(ix, 1, 0);


  glVertex3f(-1, -iy, 0);
  glVertex3f(1, -iy, 0);

  glVertex3f(-1, iy, 0);
  glVertex3f(1, iy, 0);
  glEnd();

  int i,j;
  loop(i,3){loop(j,3){
      if (board[j][i]) {drawShape(j,i,board);}
    }}
  glFlush();
  glutPostRedisplay();
}
