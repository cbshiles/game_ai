class Human : public Player {
public:

  Human(){
    type = 1;
  }
  
  void move(){
    g->humanActive = 1;
    while (g->humanActive) {}
  }
  
};
