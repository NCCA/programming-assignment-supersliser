//
// Created by thoma on 23/03/2025.
//

#include "system/TestIsBlockedSystem.h"

#include "Table.h"

void TestIsBlockedSystem::run(TransformComponents* io_component, int i_index)
{
    bool x1 = i_pos.m_x >= io_component->m_ps[i_index].m_x - 0.5f;
    bool x2 = i_pos.m_x <= io_component->m_ps[i_index].m_x + 0.5f;
    bool y1 = i_pos.m_y >= io_component->m_ps[i_index].m_y - 0.5f;
    bool y2 = i_pos.m_y <= io_component->m_ps[i_index].m_y + 0.5f;
    bool z1 = i_pos.m_z >= io_component->m_ps[i_index].m_z - 0.5f;
    bool z2 = i_pos.m_z <= io_component->m_ps[i_index].m_z + 0.5f;
    if ((x1 && x2) && (y1 && y2) && (z1 && z2))
    {
        o_output = true;
    }
}
