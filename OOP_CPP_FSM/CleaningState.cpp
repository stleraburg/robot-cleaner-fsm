#include "CleaningState.h"
#include "RobotVacuum.h"
#include "IdleState.h"  
#include <iostream>
#include "ChargingState.h"
#include "ReturningToBaseState.h"


CleaningState* CleaningState::Instance() {
    static CleaningState instance;
    return &instance;
}

void CleaningState::Enter(RobotVacuum* robot) {
    std::cout << "[Cleaning] Starting to clean...\n";
}

void CleaningState::Execute(RobotVacuum* robot) {
    std::cout << "[Cleaning] Vacuuming...\n";

    robot->DrainBattery(10);  // simulate battery usage
    robot->SetNeedsCleaning(false);  

    if (robot->GetBatteryLevel() < 100) {
        std::cout << "[Cleaning] Battery after cleaning: " << robot->GetBatteryLevel() << "\n";
    }

    if (robot->GetBatteryLevel() <= 20) {
        std::cout << "[Cleaning] Low battery! Going to charge.\n";
        robot->GetFSM()->ChangeState(ReturningToBaseState::Instance());
    } else {
        std::cout << "[Cleaning] Done cleaning. Returning to dock.\n";
        robot->GetFSM()->ChangeState(ReturningToBaseState::Instance());
    }
}

void CleaningState::Exit(RobotVacuum* robot) {
    std::cout << "[Cleaning] Finished cleaning.\n";
}

