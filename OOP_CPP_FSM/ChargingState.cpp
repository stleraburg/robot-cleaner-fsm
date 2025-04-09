#include "ChargingState.h"
#include "IdleState.h"
#include <iostream>

ChargingState* ChargingState::Instance() {
    static ChargingState instance;
    return &instance;
}

void ChargingState::Enter(RobotVacuum* robot) {
    std::cout << "[Charging] Starting to charge...\n";
}

void ChargingState::Execute(RobotVacuum* robot) {
    std::cout << "[Charging] Charging battery...\n";
    robot->RechargeBattery();

    std::cout << "[Charging] Fully charged. Switching to idle.\n";
    robot->GetFSM()->ChangeState(IdleState::Instance());
}

void ChargingState::Exit(RobotVacuum* robot) {
    std::cout << "[Charging] Leaving charging state.\n";
}

