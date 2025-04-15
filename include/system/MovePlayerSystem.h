//
// Created by s5605187 on 30/03/25.
//

#ifndef COLONYMANAGERBUILD_MOVEPLAYERSYSTEM_H
#define COLONYMANAGERBUILD_MOVEPLAYERSYSTEM_H

#include "system/System.h"
#include "component/CameraComponents.h"
#include "Table.h"
#include "component/IsSprintingComponent.h"
#include "component/SpeedComponent.h"

/// @class MovePlayerSystem include/system/MovePlayerSystem.h
/// @brief System to move the player based on input
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-30
/// @details This system moves the player based on input from the keyboard and mouse. It uses the CameraComponents to store the current position and rotation of the Player.
class MovePlayerSystem : public a_System<CameraComponents>
{
public:
    /// @brief Vector describing input direction from keyboard
    ngl::Vec3 i_dir;
    /// @brief Pointer to the world for checking collisions
    Table* i_world = nullptr;
    /// @brief Pointer to the Springing Components
    IsSprintingComponent* i_isSprinting = nullptr;
    /// @brief Pointer to the Speed Components
    SpeedComponent* i_speed = nullptr;

    /// @brief Runs the system
    /// @param[in] io_component A pointer to the CameraComponents to be moved
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_world [Optional] The world to check for collisions
    /// @param[in] i_isSprinting [Optional] The IsSprintingComponent to check if the player is sprinting
    /// @param[in] i_speed [Optional] The SpeedComponent to check the speed of the player
    void run(CameraComponents* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_MOVEPLAYERSYSTEM_H
