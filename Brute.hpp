class Rating {
  int priority, preference;

public:
  
  Rating(): priority(0), preference(-2) {}
  Rating(int pref): priority(0), preference(pref) {}

  char better_than(Rating r){
    if (preference > r.preference) return 1;
    else if (preference < r.preference) return 0;
    else return preference*priority < r.preference*r.priority;
    //creates something odd in complex situations..
  }

  void flipSides(){
    priority += 1;
    preference *= -1;
  }

  void print(){
    printf("\n Preference:%d Priority:%d \n", preference, priority);
  }
};

class Brute : public Player {

  Rating rec_move(int ti, int tj,int cplayer){
    //printf(" %d %d\n",cplayer,(cplayer%2)+1);

    board[ti][tj] = cplayer;

    // printf("\nrecursive level\n");
    //     print_board();

    Rating ans;
    
    if (check_win() > 0) ans = Rating(1);
    //The above line is only valid because you can only win on your turn in tic tac toe

    else {
      int i,j,s=0;
      Rating best,r;
      int open = 0; //# of open spots
      int full = 1;
      loop(i,3){loop(j,3){
	  if(! board[i][j]){
	    full = 0;
	    r = rec_move(i,j,(cplayer%2)+1);
	    //	    r.print();
	    if (!s++ || r.better_than(best)) {
	      //	      printf("New best! (for) player %d\n",cplayer);
	      best = r;
	    }}}}
    
      if (full) ans = Rating(0);
      else {ans = best; /* best.print(); printf(" above ,choosen ");*/}
	}
    //cycles through all possible moves, choosing best first one
    board[ti][tj] = 0;
    ans.flipSides();

    return ans;
  }

public:
    void move(){
      printf("\n\nBrute move:\n");
      int i, j, bi, bj, s=0;
      Rating best, r;

      loop(i,3){loop(j,3){
	  //	  printf("\n-- %d %d  %d --\n",i,j,board[i][j]);
	  if(! board[i][j]){
	    //	  printf("Inside: %d %d --\n",i,j);
	    r = rec_move(i,j,g->cplayer());
	    r.flipSides();
	    r.print();
	    if (!s++ || r.better_than(best)) {
	      best = r, bi=i, bj=j;
	    }}}}
      g -> place(bi, bj);
    }
};
