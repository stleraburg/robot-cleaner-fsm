#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "State.h"
#include "RobotVacuum.h" 


class IdleState : public State<RobotVacuum> {
private:
    IdleState() {}  //private constructor 

public:
    static IdleState* Instance();  // singleton

    void Enter(RobotVacuum* robot) override;
    void Execute(RobotVacuum* robot) override;
    void Exit(RobotVacuum* robot) override;

};

#endif
