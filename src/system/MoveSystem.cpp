//
// Created by s5605187 on 22/03/25.
//

#include "system/MoveSystem.h"

void MoveSystem::run(PositonComponent& i_component, int i_index)
{
    i_component.m_ps[i_index].m_x += 1;
    i_component.m_ps[i_index].m_y += 1;
    i_component.m_ps[i_index].m_z += 1;
}