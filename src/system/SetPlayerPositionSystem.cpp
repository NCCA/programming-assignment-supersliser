//
// Created by s5605187 on 06/04/25.
//

#include "system/SetPlayerPositionSystem.h"

void SetPlayerPositionSystem::run(CameraComponents* io_component, int i_index)
{
    ngl::Vec4 delta = io_component->m_cameras[i_index].getLook() - io_component->m_cameras[i_index].getEye();
    io_component->m_cameras[i_index].setEye(i_pos);
    io_component->m_cameras[i_index].setLook(i_pos + delta);
}
