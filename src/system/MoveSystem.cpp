//
// Created by s5605187 on 22/03/25.
//

#include "system/MoveSystem.h"

#include "Table.h"
#include "system/TestIsBlockedSystem.h"

void MoveSystem::run(PositonComponent* io_component, int i_index, void* i_world , std::vector<float> i_args)
{
    if (i_world == nullptr)
    {
        io_component->m_ps[i_index].m_x += i_args[0];
        io_component->m_ps[i_index].m_y += i_args[1];
        io_component->m_ps[i_index].m_z += i_args[2];
        return;
    }

    Table* world = static_cast<Table*>(i_world);
    TestIsBlockedSystem system = TestIsBlockedSystem();
    system.o_output = false;
    world->run(&system, PositonComponent::getComponentID(), {io_component->m_ps[i_index].m_x += i_args[0], io_component->m_ps[i_index].m_y += i_args[1], io_component->m_ps[i_index].m_z += i_args[2]}, world);

    if (system.o_output)
    {
        return;
    }
    io_component->m_ps[i_index].m_x += i_args[0];
    io_component->m_ps[i_index].m_y += i_args[1];
    io_component->m_ps[i_index].m_z += i_args[2];
}
