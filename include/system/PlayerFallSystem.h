//
// Created by thoma on 01/04/2025.
//

#ifndef PLAYERFALLSYSTEM_H
#define PLAYERFALLSYSTEM_H

#include "component/SpeedComponent.h"
#include "component/CameraComponents.h"
#include "system/System.h"
#include "Table.h"
#include "system/TestIsBlockedSystem.h"

/// @class PlayerFallSystem include/system/PlayerFallSystem.h
/// @brief System to handle player falling
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-04-01
/// @details This system handles the player falling by applying gravity to the player and checking for collisions with the world. It uses the CameraComponents to store the Player's position.
class PlayerFallSystem : public a_System<CameraComponents>
{
    public:
    /// @brief The gravity to be applied to the player
    SpeedComponent* i_speed = nullptr;
    /// @brief The world table to check for collisions with
    Table* i_world = nullptr;
    /// @brief Runs the system
    /// @param[in] io_component A pointer to the CameraComponents to have the gravity applied to it
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_speed [Optional] The speed component to be applied
    /// @param[in] i_world [Required] The world table to check for collisions with
    void run(CameraComponents* io_component, int i_index) override;
};

#endif //PLAYERFALLSYSTEM_H
