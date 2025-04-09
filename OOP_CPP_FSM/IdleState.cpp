#include "IdleState.h"
#include "RobotVacuum.h"
#include <iostream>
#include "CleaningState.h"

IdleState* IdleState::Instance() {
    static IdleState instance;
    return &instance;
}

void IdleState::Enter(RobotVacuum* robot) {
    std::cout << "[Idle] Entering idle mode...\n";
}

void IdleState::Execute(RobotVacuum* robot) {
    //std::cout << "[Idle] Battery: " << robot->GetBatteryLevel() << "\n";

    if (robot->NeedsCleaning()) {
        std::cout << "[Idle] Time to clean!\n";
        robot->GetFSM()->ChangeState(CleaningState::Instance());
    }
}

void IdleState::Exit(RobotVacuum* robot) {
    std::cout << "[Idle] Leaving idle mode...\n";
}

