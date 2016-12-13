class Rating {
  int priority, preference;

public:
  
  Rating(int pref): priority(0), preference(pref) {}

  char better_than(Rating r){
    if (preference > r.preference) return 1;
    else if (preference < r.preference) return 0;
    else {
      if (preference > 0) return priority < r.priority;
      else return priority > r.priority;
    }
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

    board[ti][tj] = cplayer;

    // printf("Entering layer. (%d)\n", cplayer);
    // print_board();

    Rating ans(0);

    char out = check_outcome();
    if (out >= 0)
      ans = Rating(!out?0:1);
    //The above line is only valid because you can only win on your turn in tic tac toe

    else {
      int i,j;
      Rating worst(2),r(0);
      loop(i,3){loop(j,3){
	  if(! board[i][j]){
	    r = rec_move(i,j,(cplayer%2)+1);
	    	    	    // r.print();
	    if (worst.better_than(r)) {
	      	      // printf("New worst! (for) player %d\n",cplayer); 
	      worst = r;
	    }}}}
    
      ans = worst;  //worst.print(); printf(" above ,choosen ");
    }
    //cycles through all possible moves, choosing worst first one
    board[ti][tj] = 0;
    ans.flipSides();

    // printf("Exiting layer. (%d)\n", cplayer);
    
    return ans;
  }

public:
    void move(){
      int i, j, bi, bj;
      Rating best(-2), r(0);

      loop(i,3){loop(j,3){
	  //	  printf("\n-- %d %d  %d --\n",i,j,board[i][j]);
	  if(! board[i][j]){
	    //	  printf("Inside: %d %d --\n",i,j);
	    r = rec_move(i,j,g->cplayer());
	    r.flipSides();
	    
	    if (r.better_than(best)) {
	      best = r, bi=i, bj=j;
	    }}}}
      g -> place(bi, bj);
    }
};
