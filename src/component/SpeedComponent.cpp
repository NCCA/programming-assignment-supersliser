//
// Created by thoma on 31/03/2025.
//

#include "component/SpeedComponent.h"

SpeedComponent::SpeedComponent(size_t size)
{
    m_speed.resize(size);
    for (size_t i = 0; i < size; i++)
    {
        m_speed[i] = getDefaultSpeed();
    }
}
