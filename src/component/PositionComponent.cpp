//
// Created by thoma on 22/03/2025.
//

#include "component/PositionComponent.h"

PositonComponent::PositonComponent(size_t i_size) {
    for (size_t i = 0; i < i_size; i++) {
        m_ps.push_back(ngl::Vec3());
    }
}