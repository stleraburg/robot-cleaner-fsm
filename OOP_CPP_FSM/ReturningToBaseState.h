#ifndef RETURNINGTOBASESTATE_H
#define RETURNINGTOBASESTATE_H

#include "State.h"
#include "RobotVacuum.h"

class ReturningToBaseState : public State<RobotVacuum> {
private:
    ReturningToBaseState() {}

public:
    static ReturningToBaseState* Instance();

    void Enter(RobotVacuum* robot) override;
    void Execute(RobotVacuum* robot) override;
    void Exit(RobotVacuum* robot) override;
};

#endif

