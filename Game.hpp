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

class Screen;

class Game : public Mind {
private:
  int humans, step, icp; //index of current player
  char valid;
  Player * player[2];
  Screen* screen;

  void game_step(){
    upload(player[icp]);
    valid = 0;

    player[icp]->move(); // player should make move, trigger valid

    if (! valid){
      printf("Player %d won't make a valid move.\n", cplayer());
      end_game(!icp+1);
    }

    printf("VVB\n");
    print_board();

    int out = check_outcome();
    if (out >= 0) {print_board(); end_game(out);}
    if(humans) {upload(screen); screen->drawScene();}//# watch out for!
    icp = !icp; //for next move
  }

  void end_game(int winner){
    print_board();
    printf("Winner: %d\n", winner);
    exit(1);
  }

  public:
  void loadScreen(Screen* s) {screen=s;}

  int areHumans() {return humans;}
  
  char place(int x, int y){
    char* spot = &board[x][y];
    if (! *spot){
      *spot = cplayer();
      return (valid=1);}
    return 0;
  }

  int cplayer(){return icp+1;}

  void upload(Follower* a){
    int i,j; loop(i, Y){
      loop(j, X){
	a->update(j,i,board[j][i]);
      }}}

  Game(Player *a, Player *b):
    icp(0), player{a,b}, humans(a->type + 2*b->type){
    printf("game cons\n");
    int i,j; loop(i, 2){player[i]->load(this);} //load players
    loop(i,X){loop(j,Y){board[i][j]=0;}} // load board
    print_board();
    }

  void request_move(int x, int y){

    if (place(x,y)){
      int out = check_outcome();
      if (out>=0) {print_board(); end_game(out);}
    
      icp = !icp, valid = 0; //for next move

      if ((humans==1 && icp)||(humans==2 && !icp)){
	print_board(); //# maybe remove??
	game_step();
      }
    }
  }

  void play_game(){
    if (humans) {
      if (humans==2) game_step();
      printf("hey!\n");
      glutMainLoop(); // never returns
    }
    while(1) game_step();
  }
};

void Player::move(){int i,j;
  char d=0; //for done
  loop(i, Y){ loop(j, X){
      if(! board[j][i]) {g->place(j,i); return;}
       //#can be exploited
    }}}
