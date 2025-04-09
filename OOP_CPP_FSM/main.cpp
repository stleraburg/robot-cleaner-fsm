#include <iostream>
#include <cstdlib>  
#include <ctime>    
#include <thread>    
#include <chrono>    
#include "RobotVacuum.h"

int main() {
    std::srand(std::time(0));  //seed random number generator
    RobotVacuum* robo = new RobotVacuum();

    for (int i = 0; i < 10; ++i) {
        std::cout << "\n=== Cycle " << i + 1 << " ===\n";

        // simulate dirt randomly
        int dirtChance = std::rand() % 100;
        if (dirtChance < 30) {  // 30% chance of getting dirty
            robo->SetNeedsCleaning(true);
            std::cout << "[Main] Dirt detected! Scheduling cleaning...\n";
        }

        // print battery lvl every cycle
        std::cout << "[Main] Battery level: " << robo->GetBatteryLevel() << "\n";

        // run FSM
        robo->Update();

        // a short delay for realism
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
    }

    delete robo;
    return 0;
}

