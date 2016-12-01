#include <stdio.h>
#include "MyGL.hpp"

#define loop(D, L) for(D=0; D<(L); D++)
#define bool char

//# mainly need to define Player, its move fn, and the board's validation of sed move

class Game; //forward declarationy

class Player{
  Game* g;
  int i,j;
public:
  char board[3][3];
  void load(Game* x) {g=x;}
  virtual  void move();
}; 

class Game {
private:
  char board[3][3];  
  Player * player[2];
  int icp, cplayer, i , j; //index of current player
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

  void update(Player* a){
    loop(i, 3){
      loop(j, 3){
	a->board[i][j] = board[i][j];
      }}
  }

  void print(){
    loop(i,3){
      if (i) printf("\n-----------\n");
      else printf("\n\n\n\n");
      loop(j,3){
	if (j) printf("|");
	char s = board[i][j];
	printf(" %c ", s?(s==1?'X':'O'):' ');
      }}
  }

public:
  Game(){}

  Game(Player *a, Player *b): board{0}, icp(0), player{a,b}, valid(0) {
    loop(i, 2){player[i]->load(this);}
  }

  int play_game(){ //returns winner, is called by controller
    loop(i, 9){
      print();
      cplayer = icp+1; //cplayer: player's #, as opposed to index

      update(player[icp]);
      for (j=0; !valid &&  j<20; j++){
	player[icp]->move();
	if (j >= 20) {printf("Player %d won't make a valid move.\n", cplayer); return !icp+1;}
      }
      valid = 0; //for next move
      if (check_win()) return cplayer;

      icp = !icp;
    }
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
      if(! board[i][j]) d = g->place(i,j);
      if (d) return; //weakness: Player can hang game forever
    }}
}

class Brute : public Player {

  char xtra_board[3][3];

  void move(){
    
  }

  void rec_move(){
    //know the most recent move
    //cycles through all possible moves, choosing best first one
    //undoes the move that was 'known' at the beginnning of all this
    //returns the chosen move's stats & path
  }
};

Game g;

void mouseInput(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
    g.request_move(x, y);
  }
}

int main(int argc, char* argv[]){ int i;
  Player a = Player();
  Player b = Player();
  g = Game(&a,&b);
  printf("Winner: %d\n", g.play_game());

  glutMouseFunc(mouseInput);
  
  //loop(i, argc){printf("%s\n", argv[i]);}
}
