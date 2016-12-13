#define loop(D, L) for(D=0; D<(L); D++)

class Mind{
protected:
  char board[X][Y];

  char check_outcome();

  void print_board(){
    char line[4*X];
    int i,j;
    loop(i,4*X) line[i]='-';
    line[i]=0;
    loop(i,Y){
      if (i) printf("\n%s\n", line);
      else printf("\n");
      loop(j,X){
	if (j) printf("|");
	char s = board[j][i];
	printf(" %c ", s?(s==1?'X':'O'):' ');
      }}
    printf("\n\n\n\n");
  }
};


class Follower : public Mind {
public:
  void learn (int x, int y, char v)
  {board[x][y] = v;}
};

#include "Gui.hpp"

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


class Game : public Mind {
private:
  int humans, step, icp; //index of current player
  char valid;
  Player * player[2];

  void game_step(){
    valid = 0;
    teach(player[icp]);
    player[icp]->move();

    if (!valid){
      printf("Player %d made an invalid move.\n", cplayer());
      end_game(!icp+1);
    }

    print_board(); 
    char out = check_outcome();
    if (out >= 0) end_game(out);

    if(humans){teach(screen); screen->draw();}

    icp = !icp; //for next move
  }

  void end_game(int winner){
    printf("Winner: %d\n", winner);
    exit(1);
  }
  
public:
  int humanActive;
  Screen* screen;

  char place(int x, int y);
  
  void loadScreen(Screen* s) {screen=s;}

  int areHumans() {return humans;}

  int cplayer(){return icp+1;}

  void teach(Follower* a){
    int i,j; loop(i, X){
      loop(j, Y){
	a->learn(i,j,board[i][j]);
      }}}

  Game(Player *a, Player *b): icp(0), player{a,b}{
    int i,j; loop(i, 2){player[i]->load(this);} //load players
    loop(i,X){loop(j,Y){ board[i][j]=0;}}
      // 	if (j < 3) board[i][j]=0;
      // 	else board[i][j] = 1+((i+j)%2);
      // }}
    humans = a->type + 2*b->type;
  }
  
  void play_game(){
    if (humans) {
      if (humans==2) {game_step(); screen->draw();}
      glutMainLoop(); // never returns
    }
    while(1) game_step();
  }

  void request_move(int x, int y){

    x = x*X/screen->xdim;
    y = y*Y/screen->ydim;

    if (! board[x][y] && place(x,y)){

      print_board();
      char out = check_outcome();
      if (out >= 0) end_game(out);
    
      icp = !icp, valid = 0; //for next move

      if ((humans==1 && icp)||(humans==2 && !icp)){
	game_step();
      }
    }
  }
  
};
