//
// Created by s5605187 on 30/03/25.
//

#include "system/MovePlayerSystem.h"
#include "system/TestIsBlockedSystem.h"

void MovePlayerSystem::run(CameraComponents* io_component, int i_index)
{
    TestIsBlockedSystem system;
    system.o_output = false;
    ngl::Vec3 pos = io_component->m_cameras[i_index].getPos();
    system.i_pos = pos + i_pos;
    system.i_world = i_world;
    i_world->run(&system, TransformComponents::getComponentID());

    if (system.o_output)
    {
        return;
    }
    io_component->m_cameras[i_index].move(i_pos.m_x, i_pos.m_y, i_pos.m_z);
}