//
// Created by thoma on 24/03/2025.
//

#include "system/RenderCubeSystem.h"

#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include "component/BlockComponents.h"

void RenderCubeSystem::run(BlockComponents* io_component, int i_index) {
    ngl::VAOPrimitives::draw(ngl::cube);
    auto tx = ngl::Mat4::translate(i_pos.m_x, i_pos.m_y, i_pos.m_z);
    ngl::Mat4 MVP = m_camera->m_proj[0] * m_camera->m_view[0] * tx;
    ngl::Mat3 normalMatrix = m_camera->m_view[0];
    normalMatrix.inverse().transpose();
    ngl::ShaderLib::setUniform("MVP", MVP);
    ngl::ShaderLib::setUniform("normalMatrix", normalMatrix);
}
