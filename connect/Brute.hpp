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

  char worstPossible(){
    return preference == -1 && priority == 1;
  }

  void flipSides(){
    priority += 1;
    preference *= -1;
  }

  void print(){
    printf("\n Preference:%d Priority:%d \n", preference, priority);
  }
};


int height[X]; 

class Brute : public Player {

  char check_outcome(int ti, int tj){

    char cplayer = board[ti][tj];    
    int i, z=1; loop(i,X){
      if (height[i]!=X) {z=0; break;}}
    if (z == 1) return 0;
    
    if(tj <= 2){
      if (board[ti][tj+1] == cplayer &&
	  board[ti][tj+2] == cplayer &&
	  board[ti][tj+3] == cplayer){return cplayer;}
    }

    int dlx=X-1-ti; //drx=ti,  

    int streak=1;
    for(i=1;i<ti;i++){
      if (board[ti-i][tj] == cplayer) streak++;
      else break;
    }
    for(i=1;i<dlx;i++){
      if (board[ti+i][tj] == cplayer) streak++;
      else break;
    }
    if (streak >= 4) return cplayer; streak=1;

    //up left diag
    for(i=1;i<(ti<tj?ti:tj);i++){
      if (board[ti-i][tj-i] == cplayer) streak++;
      else break;
    }
      //down right diag
    int dc,rc;
    rc = X-1-ti, dc = Y-1-tj;
    for(i=1;i<(rc<dc?rc:dc);i++){
      if (board[ti+i][tj+i] == cplayer) streak++;
      else break;
    }
    if (streak >= 4) return cplayer; streak=1;
    //up right diag
    rc = X-1-ti;
    for(i=1;i<(rc<tj?rc:tj);i++){
      if (board[ti+i][tj-i] == cplayer) streak++;
      else break;
    }

    //down left diag
    dc = Y-1-tj;
    for(i=1;i<(ti<dc?ti:dc);i++){
      if (board[ti+i][tj+i] == cplayer) streak++;
      else break;
    }
    if (streak >= 4) return cplayer;// streak=1;
    return -1;
  }

  
  Rating rec_move(int ti, int cplayer){

    int tj = Y - (height[ti]++) - 1;//one above current height (& increase height to reflect that)
    //should never be called where is creates negative index, but if its segfaults...
    board[ti][tj] = cplayer;
    

    //    printf("Entering layer. (%d)\n", cplayer);
    //  print_board();

    Rating ans(0);

    char out = check_outcome(ti,tj); //# completely change check outcome
  

    
    if (out >= 0)
      ans = Rating(!out?0:1);
    //The above line is only valid because you can only win on your turn in tic tac toe

    else {
      int i,j;
      Rating worst(2),r(0);
      loop(i,X){

	if (height[i] < Y-1){
	  r = rec_move(i, (cplayer%2)+1);
	  if (worst.better_than(r)) {
	    //printf("New worst! (for) player %d\n",cplayer);
	    if (r.worstPossible()){
	      board[ti][tj] = 0;
	      height[ti]--;
	      r.flipSides();
	      //printf("Exiting layer. (%d)\n", cplayer);
	      return r;
	    }
	    worst = r;
	  }
	}
      }	  
    
      ans = worst;  //worst.print(); printf(" above ,choosen ");
    }
    //cycles through all possible moves, choosing worst first one
    board[ti][tj] = 0;
    ans.flipSides();
    height[ti]--;
    //printf("Exiting layer. (%d)\n", cplayer);
    
    return ans;
  }

public:

  
  void move(){
    int i, j, bi, bj,h;
    Rating best(-2), r(0);

    //get heights first
    loop(i,X){for(j=Y-1, h=0;j>=0;j--){
	if(! board[i][j]){//if empty piece    
	  height[i] = h; h=0;
	  break;
	} else h++;
      } height[i] = h;
    }

    //then use to call all available options
    loop(i,X){
      if (height[i] < Y-1){
	r = rec_move(i, g->cplayer());
	r.flipSides();
	if (r.better_than(best)) {
	  best = r, bi=i, bj=j;
	}}}
    g -> place(bi, bj);
  }
};
