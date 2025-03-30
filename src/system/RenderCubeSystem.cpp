//
// Created by thoma on 24/03/2025.
//

#include "system/RenderCubeSystem.h"

#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include "component/BlockComponents.h"
void RenderCubeSystem::run(BlockTextureComponent* io_component, int i_index) {
    ngl::ShaderLib::use("TextureShader");

    // clear the screen and depth buffer
    io_component->m_vaos[i_index]->bind();
    glBindTexture(GL_TEXTURE_2D, io_component->m_GLTextureIDs[i_index]);

    // grab an instance of the shader manager

    ngl::Transformation tx;
    tx.setPosition(i_pos);
    ngl::Mat4 MVP =  i_camera->m_cameras[0].getVPMatrix() * tx.getMatrix();
    ngl::ShaderLib::setUniform("MVP", MVP);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    io_component->m_vaos[i_index]->draw();

    io_component->m_vaos[i_index]->unbind();



}