#define loop(D, L) for(D=0; D<(L); D++)
#define X 3
#define Y 3

#define check if (vert[0] && vert[0]==vert[1] && vert[0]==vert[2]) return vert[0];

class Mind{
protected:
  char board[X][Y];

  char vert[3]; //the 3 vertices in a row
  char check_win(){int i,j,k,s,add;
    loop(i,2){
      loop(j,3){loop(k,3){vert[k] = i?board[j][k]:board[k][j];}
	check}
      
      if (i) s=0, add=1;
      else s=2, add=-1;
      loop(j,3){
	vert[j] = board[j][s];
	s += add;}
      check}
    return 0;
  }

  void print_board(){
    int i,j; loop(i,3){
      if (i) printf("\n-----------\n");
      else printf("\n\n\n\n");
      loop(j,3){
	if (j) printf("|");
	char s = board[j][i];
	printf(" %c ", s?(s==1?'X':'O'):' ');
      }}
    printf("\n");
  }

};

class Follower : public Mind {
public:
  void update (int x, int y, char v)
  {board[x][y] = v;}
};

class Game;

class Player : public Follower {
protected:
  Game* g;

public:
  int type;
  Player():type(0){} //0 for non human player, 1 for human
    
  virtual void load(Game* x) {g=x;}
  virtual  void move();
};

void mouseInput(int button, int state, int x, int y);

void drawScene();

void resize(int x, int y);

class Screen : public Follower {
public:
  int xdim,ydim;

  Screen(int x, int y):xdim(x),ydim(y){
    // Initialize GLUT.
    char fakeParam[] = "GameDriver.cpp";
    char *fakeargv[] = { fakeParam, NULL };
    int fakeargc = 1;
    glutInit(&fakeargc, fakeargv);
 
    // Set display mode as single-buffered and RGB color.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
   
    // Set OpenGL window size.
    glutInitWindowSize(xdim,ydim);

    // Set position of OpenGL window upper-left corner.
    glutInitWindowPosition(100, 100); 
   
    // Create OpenGL window with title.
    glutCreateWindow("Tic-Tac-Toe");
   
    // Initialize.
    GL_init(); 

    glutMouseFunc(mouseInput);
    
    // Register display routine.
    glutDisplayFunc(drawScene); 
   
    // Register reshape routine.
    glutReshapeFunc(resize);

    glLineWidth(3);
    black->setBackground();
    white->set();
  }

  void dims(int x, int y){
    //# doesnt reallly resize..
    xdim = x, ydim = y;
  }

  float min(int z){return -.9 + z*2.0/3;}

  float max(int z){return -.433 + z*2.0/3;} 
  
  void drawShape(int x, int y){

    int shape = board[x][y];
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


  void draw(){
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
	if (board[j][i]) {printf("trying\n"); drawShape(j,i);}
      }}
  glFlush();
  //not sure when/why needed
  }

};

class Game : public Mind {
private:
  int humans, step, icp; //index of current player
  char valid;
  Player * player[2];

#define MAX_TRIES 9
  void game_step(){

    printf("step:%d\n",step);
    update(player[icp]);


    
    int j; for (j=0; !valid &&  j<=MAX_TRIES; j++){
      player[icp]->move();
      if (j >= MAX_TRIES)
  	{printf("Player %d won't make a valid move.\n", cplayer()); end_game(!icp+1);}
    }

    print_board(); 
    
    //All this needs to be done either way (below here)
    printf("AA\n");
    printf("AB%d\n",check_win());    
    if (check_win()) {print_board(); end_game(cplayer());}

    if(humans) {update(screen); screen->draw();}//#BAD
    printf("BA\n");    
    icp = !icp, valid = 0; //for next move

    step++; if (step==9) {print_board(); end_game(0);}
    printf("end of func\n");
  }

  void end_game(int winner){
    printf("Winner: %d\n", winner);
    exit(1);
  }
  
public:
  int humanActive;
  Screen* screen;

  void loadScreen(Screen* s) {screen=s;}

  int areHumans() {return humans;}
  
  char place(int x, int y){
    printf("huh %d %d %d\n",x,y,cplayer());
    char* spot = &board[x][y];
    if (! *spot){
      *spot = cplayer();
      return (valid=1);}
    return 0;
  }

  int cplayer(){return icp+1;}

  void update(Follower* a){
    int i,j; loop(i, 3){
      loop(j, 3){
	a->update(i,j,board[i][j]);
      }}}

  Game(Player *a, Player *b): icp(0), player{a,b}, valid(0){
    int i,j; loop(i, 2){player[i]->load(this);} //load players
    loop(i,X){loop(j,Y){board[i][j]=0;}} // load board

    humans = a->type + 2*b->type;
  }

  void request_move(int x, int y){

    x = x*3/screen->xdim;
    y = y*3/screen->ydim;

    printf("oh were here %d %d\n",x,y);

    if (! board[x][y] && place(x,y)){
      printf("proper move!\n");
      if (check_win()) {print_board(); end_game(cplayer());}

    
      icp = !icp, valid = 0; //for next move

      step++; if (step==9) {print_board(); end_game(0);}

      if ((humans==1 && icp)||(humans==2 && !icp)){
	printf("should be here after..\n");
	print_board();
	game_step();
      }
    
    }

  }

  void play_game(){
    if (humans) {
      if (humans==2) {game_step(); screen->draw();}
      glutMainLoop(); // never returns
    }
    while(1) game_step();
  }

};

void Player::move(){int i,j;
  char d=0; //for done
  loop(i, 3){
    loop(j, 3){
      if(! board[i][j]) { g->place(i,j); return; }
    }}
}
