//
// Created by s5605187 on 22/03/25.
//

#include "MoveSystem.h"

void MoveSystem::run(TransformComponent& i_component) {
    i_component.m_p += ngl::Vec3(1, 0, 0);
}