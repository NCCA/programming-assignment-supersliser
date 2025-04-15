//
// Created by s5605187 on 06/04/25.
//

#ifndef COLONYMANAGERBUILD_SETPLAYERPOSITIONSYSTEM_H
#define COLONYMANAGERBUILD_SETPLAYERPOSITIONSYSTEM_H

#include "System.h"
#include "component/CameraComponents.h"

/// @class SetPlayerPositionSystem include/system/SetPlayerPositionSystem.h
/// @brief System to set the player position
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-04-06
/// @details This system sets the player position based on the input from the camera component. It uses the CameraComponents to store the Player position information.
class SetPlayerPositionSystem : public a_System<CameraComponents>
{
public:
    /// @brief The position to be set when the system is run
    ngl::Vec4 i_pos;
    /// @brief runs the system
    /// @param[in] io_component A pointer to the CameraComponents to have the player position set
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_pos [Required] The position to be set
    void run(CameraComponents* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_SETPLAYERPOSITIONSYSTEM_H
