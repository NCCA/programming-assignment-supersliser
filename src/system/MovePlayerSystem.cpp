//
// Created by s5605187 on 30/03/25.
//

#include "system/MovePlayerSystem.h"
#include "system/TestIsBlockedSystem.h"

void MovePlayerSystem::run(CameraComponents* io_component, int i_index)
{

    if (i_camera == nullptr)
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
    else
    {
        auto angleDirection = i_camera->m_cameras[i_index].getYaw();
        ngl::Vec3 out = i_pos;
        out.m_x = -i_pos.m_x * cos(angleDirection) - i_pos.m_z * sin(angleDirection);
        out.m_z = i_pos.m_x * sin(angleDirection) + -i_pos.m_z * cos(angleDirection);
        out.m_y = i_pos.m_y;


        TestIsBlockedSystem system;
        system.o_output = false;
        system.i_pos = out;
        system.i_world = i_world;
        i_world->run(&system, TransformComponents::getComponentID());

        if (system.o_output)
        {
            return;
        }


        io_component->m_cameras[i_index].move(out.m_x, out.m_y, out.m_z);
    }
}