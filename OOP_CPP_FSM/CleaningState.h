#ifndef CLEANINGSTATE_H
#define CLEANINGSTATE_H

#include "State.h"
#include "RobotVacuum.h"

class CleaningState : public State<RobotVacuum> {
private:
    CleaningState() {}

public:
    static CleaningState* Instance();

    void Enter(RobotVacuum* robot) override;
    void Execute(RobotVacuum* robot) override;
    void Exit(RobotVacuum* robot) override;
};  // ✅ Now the class ends correctly here

#endif

