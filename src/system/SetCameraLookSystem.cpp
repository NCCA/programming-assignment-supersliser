//
// Created by s5605187 on 29/03/25.
//

#include "system/SetCameraLookSystem.h"

void SetCameraLookSystem::run(CameraComponents* io_component, int i_index)
{
    io_component->m_cameras[i_index].set(i_pos, i_look, ngl::Vec3::up());
}