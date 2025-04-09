#ifndef CHARGINGSTATE_H
#define CHARGINGSTATE_H

#include "State.h"
#include "RobotVacuum.h"

class ChargingState : public State<RobotVacuum> {
private:
    ChargingState() {}

public:
    static ChargingState* Instance();

    void Enter(RobotVacuum* robot) override;
    void Execute(RobotVacuum* robot) override;
    void Exit(RobotVacuum* robot) override;
};

#endif

