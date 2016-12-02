#define loop(D, L) for(D=0; D<(L); D++)
#define X 3
#define Y 3

#define check if (vert[0] && vert[0]==vert[1] && vert[0]==vert[2]) return 1;

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
	char s = board[i][j];
	printf(" %c ", s?(s==1?'X':'O'):' ');
      }}
  }

};

class Game;

class Player : public Mind {
protected:
  Game* g;

public:
  virtual void load(Game* x) {g=x;}
  virtual  void move();
  void update (int x, int y, char v)
  {board[x][y] = v;}
};

class Game : public Mind {
private:
  int icp; //index of current player
  char valid;
  Player * player[2];
  
public:  
  int cplayer(){return icp+1;}

  void update(Player* a){
    int i,j; loop(i, 3){
      loop(j, 3){
	a->update(i,j,board[i][j]);
      }}}

  Game(Player *a, Player *b): icp(0), player{a,b}, valid(0) {
    int i,j; loop(i, 2){player[i]->load(this);}
    loop(i,X){loop(j,Y){board[i][j]=0;}}
  }

  //  int request_move(int x, int y){}
#define MAX_TRIES 9
  
  int play_game(){ //returns winner, is called by controller
    int i,j; loop(i, 9){

      print_board();
      
      update(player[icp]);
      for (j=0; !valid &&  j<=MAX_TRIES; j++){
	player[icp]->move();
	if (j >= MAX_TRIES)
	  {printf("Player %d won't make a valid move.\n", cplayer()); return !icp+1;}
      }

      if (check_win()) {print_board(); return cplayer();}

      icp = !icp, valid = 0; //for next move
    }
    print_board();
    return 0; //Tie
  }

  char place(int x, int y){

    char* spot = &board[x][y];
    if (! *spot){
      *spot = cplayer();
      return (valid=1);}
    return 0;
  }

};

void Player::move(){int i,j;
  char d=0; //for done
  loop(i, 3){
    loop(j, 3){
      if(! board[i][j]) { g->place(i,j); return; }
    }}
}

#include "Brute.hpp"
