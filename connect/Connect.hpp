#define X 7
#define Y 6
#define SQR 125 //1 dimension of a square
#define GAME "Connect-4"

#include "../Core.hpp"

//returns a players# if winner, 0 for tie, -1 for unfinished
char Mind::check_outcome(){int i,j;
  //horizontals
  //printf("horizontals\n");
  char ci=0,nci; int cs=0; //current item, current streak
  char full = 1;
  loop(i,Y){
    loop(j,X){
      if (nci =  board[j][i]){
	if (nci == ci){
	  cs++;
	  if (cs == 4) return ci;
	}
	else {ci=nci; cs=1;}
      }
      else cs=ci=full=0;
    }
    cs=ci=0;
  }

  if (full) return 0;

  //verts
  //printf("verticals\n");
  loop(i,X){
    for(j=Y-1;j>=0;j--){
      if (nci =  board[i][j]){
	if (nci == ci){
	  cs++;
	  if (cs == 4) return ci;
	}
	else {ci=nci; cs=1;}
      }
      else break;
    }
    cs=ci=0;
  }

  int xo, yo;
  int ix, iy;

  //diags

  //printf("diags\n");

  //the 'higher' it is from our persp, the lower the index
  
  //downs
  xo=0,yo=Y-4;
  ix=1,iy=1;

  for(;yo>0;yo--){
    for(i=0;xo+i*ix<X && yo+i*iy<Y;i++){
      //printf("%d %d - ",xo+i*ix,yo+i*iy);
      if (nci =  board[xo+i*ix][yo+i*iy]){
	if (nci == ci){
	  cs++;
	  if (cs == 4) return ci;
	}
	else {ci=nci; cs=1;}
      }
      else cs=ci=0;
    }
    cs=ci=0;
    //printf("\n");
  }

  for(xo=0;xo<X-3;xo++){
    for(i=0;xo+i*ix<X && yo+i*iy<Y;i++){
     //printf("%d %d - ",xo+i*ix,yo+i*iy);

      if (nci =  board[xo+i*ix][yo+i*iy]){
	if (nci == ci){
	  cs++;
	  if (cs == 4) return ci;
	}
	else {ci=nci; cs=1;}
      }
      else cs=ci=0;
    }
    cs=ci=0;
    //printf("\n");
  }
  
  //ups

  xo=0,yo=3;
  ix=1,iy=-1;


  for(;yo<Y-1;yo++){
    for(i=0;xo+i*ix<X && yo+i*iy>=0;i++){
          //printf("%d %d - ",xo+i*ix,yo+i*iy);
      if (nci =  board[xo+i*ix][yo+i*iy]){
	if (nci == ci){
	  cs++;
	  if (cs == 4) return ci;
	}
	else {ci=nci; cs=1;}
      }
      else cs=ci=0;
    }
    cs=ci=0;
        //printf("\n");
  }
  for(xo=0;xo<X-3;xo++){
    for(i=0;xo+i*ix<X && yo+i*iy>=0;i++){
      //printf("%d %d - ",xo+i*ix,yo+i*iy);
      if (nci =  board[xo+i*ix][yo+i*iy]){
	if (nci == ci){
	  cs++;
	  if (cs == 4) return ci;
	}
	else {ci=nci; cs=1;}
      }
      else cs=ci=0;
    }
    cs=ci=0;
        //printf("\n");
  }
  return -1;
}


char Game::place(int x, int y){
  printf("%d %d\n",x,y);
  int iy=Y;
  while (--iy>y){
    if (! board[x][iy]) return 0;
  }

  if (board[x][y]) return 0;
  board[x][y] = cplayer();
  return (valid=1);
}

void Player::move(){int i, j;
  loop(i,X){
    for(j=Y-1;j>=0;j--){
      if(! board[i][j]) { g->place(i,j); return; }
    }}
}


void Screen::init(){}

void drawShape(int x, int y, char p){
  y = Y - y - 1;
  float xo = 2.0*(x+.15)/X-1;
  float yo = 2.0*(y+.15)/Y-1;
  float w = 1.4/X; //.7 (% width) * 2 [total screen width 2]
  float h = 1.4/Y;

  if (p==1) red->set();
  else blue->set();

  glBegin(GL_POLYGON);
  glVertex3f(xo,yo+h,0);
  glVertex3f(xo,yo,0);
  glVertex3f(xo+w,yo,0);
  glVertex3f(xo+w,yo+h,0);
  glEnd();
}

void Screen::draw(){
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

  black->setBackground();
  yellow->set();
  
  //rest of stuff
  int i,j;
  float row = 2.0/X; //from -1 to 1
  float thick = .15*row;
  float xo=-1;
  for(i=0; i<=X;i++){
    char az = !i || i==X; //if 1st or last row
    float it = az?thick:2*thick;
    glBegin(GL_POLYGON);
    glVertex3f(xo, -1, 0);
    glVertex3f(xo, 1, 0);
    glVertex3f(xo+it, 1, 0);
    glVertex3f(xo+it, -1, 0);
    glEnd();
    xo += az?row-it:row;
  }

  float col = 2.0/Y; //from -1 to 1
  thick = .15*col;
  float yo=-1;
  for(i=0; i<=Y;i++){
    char az = !i || i==Y; //if 1st or last column
    float it = az?thick:2*thick;
    glBegin(GL_POLYGON);


    glVertex3f(-1, yo+it, 0);
    glVertex3f(-1, yo, 0);
    glVertex3f(1, yo, 0);
    glVertex3f(1, yo+it, 0);	   
    glEnd();
    yo += az?col-it:col;
  }


  loop(i,Y){loop(j,X){
      if (board[j][i]) {drawShape(j,i,board[j][i]);}
    }}
  glFlush();
  glutPostRedisplay();
}
