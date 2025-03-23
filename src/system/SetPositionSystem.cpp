//
// Created by thoma on 22/03/2025.
//

#include "system/SetPositionSystem.h"

void SetPositionSystem::run(PositonComponent* io_component, int i_index, void* i_world, std::vector<float> i_args)
{
    if (i_args.size() < 4) {
        throw std::invalid_argument("Insufficient arguments");
    }
    io_component->m_ps[i_args[0]].m_x = i_args[1];
    io_component->m_ps[i_args[0]].m_y = i_args[2];
    io_component->m_ps[i_args[0]].m_z = i_args[3];
}
