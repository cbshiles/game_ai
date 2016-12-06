#define loop(D, L) for(D=0; D<(L); D++)
#define X 3
#define Y 3

#define check if (vert[0] && vert[0]==vert[1] && vert[0]==vert[2]) return vert[0];

class Mind{
protected:
  char board[X][Y];

  char vert[3]; //the 3 vertices in a row, will change 4 connect4

  //returns a players# if winner, 0 for tie, -1 for unfinished
  char check_outcome(){int i,j,k,s,add; 
    char full=1;
    loop(i,2){
      loop(j,3){loop(k,3){
	  if (i) vert[k] = board[j][k];
	  else full &= (vert[k] = board[k][j]);
	}check}
      
      if (i) s=0, add=1;
      else s=2, add=-1;
      loop(j,3){
	vert[j] = board[j][s];
	s += add;}
      check}
    return full?0:-1;
  }

  void print_board(){
    int i,j; loop(i,X){
      if (i) printf("\n-----------\n");
      else printf("\n\n\n\n");
      loop(j,Y){
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

