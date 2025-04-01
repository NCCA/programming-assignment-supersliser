//
// Created by thoma on 01/04/2025.
//

#include "system/PlayerFallSystem.h"

void PlayerFallSystem::run(CameraComponents* io_component, int i_index)
{
    float sp;
    if (i_speed == nullptr)
    {
        sp = SpeedComponent::getDefaultSpeed();
    }
    else
    {
        sp = i_speed->m_speed[i_index];
    }
    TestIsBlockedSystem testIsBlockedSystem;
    ngl::Vec3 newPos = io_component->m_cameras[i_index].getPos();
    newPos.m_y -= sp - 1.0f;
    testIsBlockedSystem.i_world = i_world;
    testIsBlockedSystem.i_pos = newPos;

    i_world->run(&testIsBlockedSystem, TransformComponents::getComponentID());
    if (testIsBlockedSystem.o_output)
    {
       newPos.m_y = std::floor(newPos.m_y + 1.0f);
    }

    io_component->m_cameras[i_index].move(newPos.m_x - io_component->m_cameras[i_index].getPos().m_x,
                                         newPos.m_y - io_component->m_cameras[i_index].getPos().m_y,
                                         newPos.m_z - io_component->m_cameras[i_index].getPos().m_z);
}