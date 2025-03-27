//
// Created by thoma on 24/03/2025.
//

#include "system/RenderCubeSystem.h"

#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include "component/BlockComponents.h"
void RenderCubeSystem::run(BlockTextureComponent* io_component, int i_index) {

    // clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // grab an instance of the shader manager
    ngl::ShaderLib::use("TextureShader");

    io_component->m_vaos[i_index]->bind();
    io_component->m_vaos[i_index]->draw();
    glBindTexture(GL_TEXTURE_2D, io_component->m_GLTextureIDs[i_index]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    io_component->m_vaos[i_index]->unbind();


    auto tx = ngl::Mat4::translate(0.0f, -0.45f, 0.0f);
    ngl::Mat4 MVP =  m_camera->m_proj[0] * m_camera->m_view[0] * tx;
    ngl::ShaderLib::setUniform("MVP", MVP);
}