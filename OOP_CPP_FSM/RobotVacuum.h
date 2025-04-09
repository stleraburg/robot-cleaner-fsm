#ifndef ROBOTVACUUM_H
#define ROBOTVACUUM_H

#include "StateMachine.h"

class RobotVacuum {
private: 
    StateMachine<RobotVacuum>* fsm;
    int batteryLvl;
    bool needsCleaning;

public: 
    RobotVacuum();  //constructor
    ~RobotVacuum();  //destructor

    void Update();

    StateMachine<RobotVacuum>* getFSM() const { 
	return fsm; 
    }


    int GetBatteryLevel() const { 
	return batteryLvl; 
    }


    void DrainBattery(int amount) { 
	batteryLvl -= amount; 
    }


    void SetNeedsCleaning(bool value) { 
	needsCleaning = value; 
    }


    bool NeedsCleaning() const { 
	return needsCleaning; 
    }


    void RechargeBattery() { 
	batteryLvl = 100; 
    }


    StateMachine<RobotVacuum>* GetFSM() const { 
	return fsm; 
    }


};


#endif
