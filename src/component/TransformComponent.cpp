//
// Created by thoma on 22/03/2025.
//

#include "component/TransformComponent.h"

TransformComponent::TransformComponent(size_t i_size) {
    for (size_t i = 0; i < i_size; i++) {
        m_ps.push_back(ngl::Vec3());
        m_rs.push_back(ngl::Quaternion());
        m_ss.push_back(ngl::Vec3(1.0f, 1.0f, 1.0f));
    }
}