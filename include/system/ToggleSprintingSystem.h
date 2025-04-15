#ifndef TOGGLESPRINTINGSYSTEM_H
#define TOGGLESPRINTINGSYSTEM_H

#include "System.h"
#include "component/IsSprintingComponent.h"

/// @class ToggleSprintingSystem include/system/ToggleSprintingSystem.h
/// @brief System to toggle the sprinting state of an entity
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-26
/// @details This system toggles the sprinting state of an entity based on input. It uses the IsSprintingComponent to store the sprinting state.
class ToggleSprintingSystem : public a_System<IsSprintingComponent> {
    public:
      /// @brief runs the system
        /// @param i_ioComponent A pointer to the IsSprintingComponent to have the sprinting state toggled
        /// @param i_index The index of the entity in the parent table
        void run(IsSprintingComponent* i_ioComponent, int i_index) override;
};

#endif // TOGGLESPRINTINGSYSTEM_H
