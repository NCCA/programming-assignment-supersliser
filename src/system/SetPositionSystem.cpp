//
// Created by thoma on 22/03/2025.
//

#include "system/SetPositionSystem.h"

void SetPositionSystem::run(TransformComponents* io_component, int i_index)
{
    io_component->m_ps[i_index].m_x = i_pos.m_x;
    io_component->m_ps[i_index].m_y = i_pos.m_y;
    io_component->m_ps[i_index].m_z = i_pos.m_z;
}
