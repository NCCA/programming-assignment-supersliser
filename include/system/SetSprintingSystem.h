#ifndef SETSPRINTINGSYSTEM_H
#define SETSPRINTINGSYSTEM_H

#include "System.h"
#include "component/IsSprintingComponent.h"

/// @class SetSprintingSystem include/system/SetSprintingSystem.h
/// @brief System to set the sprinting state of an entity
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-26
/// @details This system sets the sprinting state of an entity based on the input from the player. It uses the IsSprintingComponent to store the sprinting state.
class SetSprintingSystem : public a_System<IsSprintingComponent> {
    public:
      /// @brief The state to set
        bool i_value;
        /// @brief runs the system
        /// @param[in] i_ioComponent A pointer to the IsSprintingComponent to have the sprinting state set
        /// @param[in] i_index The index of the entity in the parent table
        /// @param[in] i_value [Required] The sprinting state to be set
        void run(IsSprintingComponent* i_ioComponent, int i_index) override;
};
#endif // SETSPRINTINGSYSTEM_H
