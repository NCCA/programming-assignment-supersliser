#ifndef TOGGLESPRINTINGSYSTEM_H
#define TOGGLESPRINTINGSYSTEM_H

#include "System.h"
#include "component/IsSprintingComponent.h"

class ToggleSprintingSystem : public a_System<IsSprintingComponent> {
    public:
        void run(IsSprintingComponent* i_ioComponent, int i_index) override;
};

#endif // TOGGLESPRINTINGSYSTEM_H
