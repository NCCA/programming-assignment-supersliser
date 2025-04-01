//
// Created by s5605187 on 30/03/25.
//

#include "system/MovePlayerSystem.h"
#include "system/TestIsBlockedSystem.h"

void MovePlayerSystem::run(CameraComponents* io_component, int i_index)
{
    i_dir.m_z = -i_dir.m_z;
    i_dir.m_x = -i_dir.m_x;
    ngl::Vec3 currentPos = io_component->m_cameras[i_index].getPos();
    ngl::Vec3 currentDir = i_dir * (i_speed != nullptr ? i_speed->m_speed[i_index] : SpeedComponent::getDefaultSpeed());


    //Is Sprinting?
    if (i_isSprinting != nullptr)
    {
        if (i_isSprinting->m_isSprinting[i_index])
        {
            currentDir *= 2.0f; // Double the speed if sprinting
        }
    }

    //Calculate new location
    ngl::Vec3 newPos = currentPos;
    auto angleDir = io_component->m_cameras[i_index].getYaw();
    ngl::Real originalX = currentDir.m_x;
    ngl::Real originalZ = currentDir.m_z;
    currentDir.m_x = originalX * cos(angleDir) + originalZ * sin(angleDir);
    currentDir.m_z = -originalX * sin(angleDir) + originalZ * cos(angleDir);

    newPos += currentDir;
    newPos.m_y = currentPos.m_y - 1.0f;

    if (i_world == nullptr)
    {
        io_component->m_cameras[i_index].move(currentDir.m_x, currentDir.m_y, currentDir.m_z);
        return;
    }

    const float feetHeight = currentPos.m_y - 1.0f;

    TestIsBlockedSystem t;
    const uint8_t tid = TransformComponents::getComponentID();
    t.i_pos = newPos;
    t.i_world = i_world;
    i_world->run(&t, tid);
    //o_output == true means the new position is blocked
    if (t.o_output)
    {
        t.i_pos.m_y = feetHeight + 1.0f;
        t.o_output = false;
        t.i_world->run(&t, tid);
        if (t.o_output)
        {
            return;
        }
        else
        {
            t.i_pos.m_y = feetHeight + 2.0f;
            t.o_output = false;
            t.i_world->run(&t, tid);
            if (t.o_output)
            {
                return;
            }
            else
            {
                t.i_pos = currentPos;
                t.i_pos.m_y = feetHeight + 2.0f;
                t.o_output = false;
                t.i_world->run(&t, tid);
                if (t.o_output)
                {
                    return;
                }
                else
                {
                    io_component->m_cameras[i_index].move(currentDir.m_x, +1, currentDir.m_z);
                    return;
                }
            }
        }
    }
    else
    {
        t.i_pos.m_y = feetHeight + 1.0f;
        t.o_output = false;
        t.i_world->run(&t, tid);
        if (t.o_output)
        {
            return;
        }
        else
        {
                io_component->m_cameras[i_index].move(currentDir.m_x, 0, currentDir.m_z);
                return;
        }
    }
}