
class Human : public Player {
public:

  Human(){
    type = 1;
  }

  //move should never be called, so can inherit from Player

};
