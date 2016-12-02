class Rating {
  int priority, preference;

public:
  
  Rating(): priority(12), preference(-1) {}
  Rating(int pref): priority(0), preference(pref) {}

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
    cplayer = g->cplayer();
    printf("virt load %d\n", cplayer);
  }
  
  Rating rec_move(int ti, int tj){
    printf("heya %d %d %d\n",ti,tj,cplayer);
    int i,j,s=0;
    board[ti][tj] = cplayer;
    int c = check_win();
    if (c >= 0) return Rating(c);

    Rating best,r;

    loop(i,3){loop(j,3){
	if(! board[i][j]){
	  printf("aloha %d %d\n",i,j);
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
	  printf("\n-- %d %d  %d --\n",i,j,board[i][j]);
	  if(! board[i][j]){
	  printf("Inside: %d %d --\n",i,j);
	    r = rec_move(i,j);
	    if (!s++ || r.better_than(best)) {
	      best = r, bi=i, bj=j;
	    }}}}
      g -> place(bi, bj);
  }
};
