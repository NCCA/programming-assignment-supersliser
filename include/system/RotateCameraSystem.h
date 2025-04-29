//
// Created by thoma on 30/03/2025.
//

#ifndef ROTATECAMERASYSTEM_H
#define ROTATECAMERASYSTEM_H

#include <component/CameraComponents.h>
#include "system/System.h"

/// @class RotateCameraSystem include/system/RotateCameraSystem.h
/// @brief System to handle camera rotation
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-30
/// @details This system handles the camera rotation by applying the mouse delta to the camera's rotation. It uses the CameraComponents to store the camera's position and rotation.
class RotateCameraSystem : public a_System<CameraComponents>
{
    public:
    /// @brief The mouse delta to be applied to the camera
    ngl::Vec2 i_mouseDelta;
    /// @brief The sensitivity of the camera rotation
    float s_sensitivity = 0.075f;
    /// @brief Runs the system
    /// @param[in] io_component A pointer to the CameraComponents to have the rotation applied to it
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_mouseDelta [Required] The mouse delta to be applied
    /// @param[in] s_sensitivity [Optional] The sensitivity of the camera rotation
    void run(CameraComponents* io_component, int i_index) override;
};

#endif //ROTATECAMERASYSTEM_H
