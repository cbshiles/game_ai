#include <stdio.h>
#include "MyGL.hpp"

#define loop(D, L) for(D=0; D<(L); D++)
#define bool char

//# mainly need to define Player, its move fn, and the board's validation of sed move

class Game; //forward declarationy

class Player{
protected:
  int i,j;
  Game* g;

public:
  char board[3][3];
  virtual void load(Game* x) {printf("Loaded!\n"); g=x;}
  virtual  void move();
}; 

class Game {
private:
  char board[3][3];  
  Player * player[2];
  int icp, cplayer; //index of current player
  char valid;

  //Check board for win
  char vert[3]; //the 3 vertices in a row
#define check if (vert[0] && vert[0]==vert[1] && vert[0]==vert[2]) return 1;


  bool check_win(){int i,j,k,s,add;
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
  
public:  
  bool u_check_win(char* bd){int i,j,k,s,add;
    loop(i,2){
      loop(j,3){loop(k,3){vert[k] = i?bd[j*3 + k]:bd[k*3 + j];}
	check}
      
      if (i) s=0, add=1;
      else s=2, add=-1;
      loop(j,3){
	vert[j] = bd[j*3 + s];
	s += add;}
      check}
    return 0;
  }

  
  void update(Player* a){
    int i,j; loop(i, 3){
      loop(j, 3){
	a->board[i][j] = board[i][j];
      }}}

  void print(){
    int i,j; loop(i,3){
      if (i) printf("\n-----------\n");
      else printf("\n\n\n\n");
      loop(j,3){
	if (j) printf("|");
	char s = board[i][j];
	printf(" %c ", s?(s==1?'X':'O'):' ');
      }}
  }


  Game(){}

  Game(Player *a, Player *b): board{0}, icp(0), player{a,b}, valid(0) {
    int i; loop(i, 2){player[i]->load(this);}
  }

  int get_cplayer(){return cplayer;}

  int request_move(int x, int y){}

#define MAX_TRIES 9
  
  int play_game(){ //returns winner, is called by controller
    int i,j; loop(i, 9){

      print();
      cplayer = icp+1; //cplayer: player's #, as opposed to index
      
      update(player[icp]);
      for (j=0; !valid &&  j<=MAX_TRIES; j++){
	player[icp]->move();
	if (j >= MAX_TRIES)
	  {printf("Player %d won't make a valid move.\n", cplayer); return !icp+1;}
      }
      valid = 0; //for next move
      if (check_win()) {print(); return cplayer;}

      icp = !icp;
    }
    print();
    return 0; //Tie
  }

  bool place(int x, int y){

    char* spot = &board[x][y];
    if (! *spot){
      *spot = cplayer;
      return (valid=1);}
    return 0;
  }
  };

void Player::move(){
  bool d=0; //for done
  loop(i, 3){
    loop(j, 3){
      if(! board[i][j]) { g->place(i,j); return; }
    }}
}

class Rating {
  int priority, preference;

public:
  
  Rating(): priority(12), preference(-1) {}
  Rating(int real): priority(0), preference(1) {}

  char better_than(Rating r){
    if (preference > r.preference) return 1;
    else if (preference < r.preference) return 0;
    else if (preference == 1) return priority < r.priority;
    else return priority > r.priority;
  }

  void flipSides(){
    priority += 1;
    preference *= -1;
  }
};

class Brute : public Player {

  int cplayer;

  void load(Game* x){
    g=x;
    cplayer = g->get_cplayer();
  }
  
  Rating rec_move(int ti, int tj){
    printf("heya %d %d\n",ti,tj);
    int i,j,s=0;
    board[ti][tj] = cplayer;
    if (g -> u_check_win(&board[0][0])) return Rating(0);

    Rating best,r;

    loop(i,3){loop(j,3){
	if(! board[i][j]){
	  r = rec_move(i,j);
	  if (!s++ || r.better_than(best)) {
	    best = r;
	  }}}}
    
    //cycles through all possible moves, choosing best first one
    board[ti][tj] = 0;
    best.flipSides();
    return best;
  }

public:
    void move(){

      int i, j, bi, bj, s=0;
      Rating best, r;

      loop(i,3){loop(j,3){
	  printf("\n-- %d %d --\n",i,j);
	  if(! board[i][j]){
	    r = rec_move(i,j);
	    if (!s++ || r.better_than(best)) {
	      best = r, bi=i, bj=j;
	    }}}}
      g -> place(bi, bj);
  }
};

Player *a = new Player();
Player *b = new Brute();
Game mainGame = Game(a,b);

void mouseInput(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
    mainGame.request_move(x, y);
  }
}

int main(int argc, char* argv[]){ int i;
   printf("Winner: %d\n", mainGame.play_game());

  //  glutMouseFunc(mouseInput);
  
  //loop(i, argc){printf("%s\n", argv[i]);}
}
