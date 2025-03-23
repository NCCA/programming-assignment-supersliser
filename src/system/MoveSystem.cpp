//
// Created by s5605187 on 22/03/25.
//

#include "system/MoveSystem.h"

#include "Table.h"
#include "system/TestIsBlockedSystem.h"

void MoveSystem::run(TransformComponent* io_component, int i_index)
{
    if (i_world == nullptr)
    {
        io_component->m_ps[i_index].m_x += i_pos.m_x;
        io_component->m_ps[i_index].m_y += i_pos.m_y;
        io_component->m_ps[i_index].m_z += i_pos.m_z;
        return;
    }

    Table* world = i_world;
    TestIsBlockedSystem system;
    system.o_output = false;
    system.i_pos = io_component->m_ps[i_index] + i_pos;
    system.i_world = world;
    world->run(&system, TransformComponent::getComponentID());

    if (system.o_output)
    {
        return;
    }
    io_component->m_ps[i_index].m_x += i_pos.m_x;
    io_component->m_ps[i_index].m_y += i_pos.m_y;
    io_component->m_ps[i_index].m_z += i_pos.m_z;
}
