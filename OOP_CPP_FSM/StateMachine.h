#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <cassert>

template <class T>
class State;

template <class T>
class StateMachine {
private: 
    T* owner;  // pointer to the agent using this fsm (RobotVacuum)
    State<T>* currentState;

public:
    StateMachine(T* owner) : owner(owner), currentState(nullptr) {}

    void ChangeState(State<T>* newState) {
        assert(newState && "New state must not be null!");

        if (currentState) {
            currentState->Exit(owner);
        }

        currentState = newState;
        currentState->Enter(owner);
    }


    void Update() {
        if (currentState) {
            currentState->Execute(owner);
        }
     }


    State<T>* GetCurrentState() const {
        return currentState;
    }

};


#endif
