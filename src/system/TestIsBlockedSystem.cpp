//
// Created by thoma on 23/03/2025.
//

#include "system/TestIsBlockedSystem.h"

#include "Table.h"

void TestIsBlockedSystem::run(TransformComponents* io_component, int i_index)
{
    if (io_component->m_ps[i_index].m_x == i_pos.m_x && io_component->m_ps[i_index].m_y == i_pos.m_y && io_component->m_ps[i_index].m_z == i_pos.m_z)
    {
        o_output = true;
    }
}
