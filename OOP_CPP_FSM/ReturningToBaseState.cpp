#include "ReturningToBaseState.h"
#include "RobotVacuum.h"
#include "IdleState.h"
#include <iostream>
#include "ChargingState.h"

ReturningToBaseState* ReturningToBaseState::Instance() {
    static ReturningToBaseState instance;
    return &instance;
}

void ReturningToBaseState::Enter(RobotVacuum* robot) {
    std::cout << "[Returning] Heading back to base...\n";
}

void ReturningToBaseState::Execute(RobotVacuum* robot) {
    std::cout << "[Returning] Navigating to docking station...\n";
    std::cout << "[Returning] Docked. \n";
    robot->GetFSM()->ChangeState(ChargingState::Instance());
}

void ReturningToBaseState::Exit(RobotVacuum* robot) {
    std::cout << "[Returning] Leaving return-to-base state.\n";
}

