#include "RobotVacuum.h"
#include "StateMachine.h"
#include "IdleState.h"
#include <iostream>

// Constructor 
RobotVacuum::RobotVacuum() {
    batteryLvl = 100; 
    needsCleaning = true;

    fsm = new StateMachine<RobotVacuum>(this);
    fsm->ChangeState(IdleState::Instance());  //setting start state 

}

// Destructor
RobotVacuum::~RobotVacuum() {
    delete fsm;
}


void RobotVacuum::Update() {
    fsm->Update();
}

