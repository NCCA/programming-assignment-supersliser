//
// Created by thoma on 23/03/2025.
//

#include "system/TestIsBlockedSystem.h"

#include "Table.h"

void TestIsBlockedSystem::run(PositonComponent* io_component, int i_index, void* i_world, std::vector<float> i_args)
{
    if (io_component->m_ps[i_index].m_x == i_args[0] && io_component->m_ps[i_index].m_y == i_args[1] && io_component->m_ps[i_index].m_z == i_args[2])
    {
        o_output = true;
    }
}
