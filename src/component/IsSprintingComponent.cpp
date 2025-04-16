//
// Created by thoma on 30/03/2025.
//

#include "component/IsSprintingComponent.h"

IsSprintingComponent::IsSprintingComponent(size_t i_size)
{
    for (size_t i = 0; i < i_size; i++)
    {
        m_isSprinting.push_back(false);
    }
}
