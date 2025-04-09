#ifndef STATE_H
#define STATE_H

template <class T>

class State {
public:

  virtual ~State(){}

  //this will execute when the state is entered
  virtual void Enter(T*)=0;

  //this is the state's normal update function
  virtual void Execute(T*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void Exit(T*)=0;

};

#endif


