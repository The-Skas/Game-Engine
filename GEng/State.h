//State.h//
//This class will serve as an interface to the class of type State.
//This class will have derived classes that serve as different 
//behaviours an entity can execute.
#ifndef GENG_SRC_STATE_H_
#define GENG_SRC_STATE_H_
template <class T>
class State
{
public:
  State() {};
  ~State(){};
  //Called to enter a new state
  virtual void enter(T * pointer) =0;

  //called on frame to execute the current behaviour
  virtual void execute(T * type) =0;
  
  //exits a state
  virtual void exit( T * type)=0;
};
#endif