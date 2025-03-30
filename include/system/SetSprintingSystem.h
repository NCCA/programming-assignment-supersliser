#ifndef SETSPRINTINGSYSTEM_H
#define SETSPRINTINGSYSTEM_H

#include "System.h"
#include "component/IsSprintingComponent.h"

class SetSprintingSystem : public a_System<IsSprintingComponent> {
    public:
        bool i_value;
        void run(IsSprintingComponent* i_ioComponent, int i_index) override;
};
#endif // SETSPRINTINGSYSTEM_H
