//
// Created by s5605187 on 29/03/25.
//

#ifndef COLONYMANAGERBUILD_SETCAMERALOOKSYSTEM_H
#define COLONYMANAGERBUILD_SETCAMERALOOKSYSTEM_H

#include "component/CameraComponents.h"
#include "System.h"

/// @class SetCameraLookSystem include/system/SetCameraLookSystem.h
/// @brief System to set the camera look direction
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-29
/// @details This system sets the camera look direction based on the input from the user. It uses the CameraComponents to store the camera information.
class SetCameraLookSystem : public a_System<CameraComponents>
{
public:
  /// @brief runs the system
    /// @param[in] io_component A pointer to the CameraComponents to have the camera look direction set
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_pos [Required] The camera position to be set
    /// @param[in] i_look [Required] The camera look direction to be set
    void run(CameraComponents* io_component, int i_index) override;
    /// @brief The camera position to be set when the system is run
    ngl::Vec3 i_pos;
    /// @brief The camera look direction to be set when the system is run
    ngl::Vec3 i_look;
};

#endif //COLONYMANAGERBUILD_SETCAMERALOOKSYSTEM_H
