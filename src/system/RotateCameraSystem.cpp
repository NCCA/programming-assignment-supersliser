//
// Created by thoma on 30/03/2025.
//

#include "system/RotateCameraSystem.h"

void RotateCameraSystem::run(CameraComponents* io_component, int i_index)
{
    auto& camera = io_component->m_cameras[i_index];

    float yaw = -i_mouseDelta.m_x * s_sensitivity;
    float pitch = i_mouseDelta.m_y * s_sensitivity;

    // Apply yaw and pitch
    camera.yaw(yaw);
    camera.pitch(pitch);
}