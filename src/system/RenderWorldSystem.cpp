//
// Created by thoma on 24/03/2025.
//

#include "system/RenderWorldSystem.h"

#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>

#include "component/BlockComponents.h"
#include "component/TransformComponents.h"
#include "component/BlockTextureComponent.h"

void RenderWorldSystem::run(CameraComponents* io_component, int i_index) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < static_cast<TransformComponents*>(i_world->getColumn(i_world->getComponentIndex(TransformComponents::getComponentID())).get())->m_ps.size(); i++)
    {
        ngl::ShaderLib::use("TextureShader");

        std::shared_ptr<ngl::AbstractVAO> vao = (static_cast<BlockTextureComponent*>(i_world->getColumn(i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get()))->m_vaos[i];
        uint8_t blockTextureComponent = (static_cast<BlockTextureComponent*>(i_world->getColumn(i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get()))->m_textureIDs[i];

        // clear the screen and depth buffer
        vao->bind();
        glBindTexture(GL_TEXTURE_2D, blockTextureComponent);

        // grab an instance of the shader manager

        ngl::Transformation tx;
        tx.setPosition(static_cast<TransformComponents*>(i_world->getColumn(i_world->getComponentIndex(TransformComponents::getComponentID())).get())->m_ps[i]);
        ngl::Mat4 MVP =  io_component->m_cameras[0].getVPMatrix() * tx.getMatrix();
        ngl::ShaderLib::setUniform("MVP", MVP);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        vao->draw();

        vao->unbind();
    }

}
