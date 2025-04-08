//
// Created by thoma on 24/03/2025.
//

#include "system/RenderWorldSystem.h"

#include <ngl/Mat4.h>
#include <ngl/MultiBufferVAO.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>

#include "component/BlockComponents.h"
#include "component/TransformComponents.h"
#include "component/BlockTextureComponent.h"

void RenderWorldSystem::run(CameraComponents* io_component, int i_index) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<std::shared_ptr<MultiBufferInstanceVAO>> vaos =
        (static_cast<BlockTextureComponent*>(i_world->getColumn(i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get()))->s_trueVaos;
    std::vector<uint8_t> texs =
        (static_cast<BlockTextureComponent*>(i_world->getColumn(i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get()))->m_textureIDs;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    std::vector<ngl::Vec3> pos = static_cast<TransformComponents*>(i_world->getColumn(i_world->getComponentIndex(TransformComponents::getComponentID())).get())->m_ps;

    for (int i = 1; i < vaos.size(); i++)
    {
        ngl::ShaderLib::use("TextureShader");

        MultiBufferInstanceVAO* vao = vaos[i].get();
        vao->bind();
        //
        // vao->setData(ngl::MultiBufferVAO::VertexData(sizeof(pos[i]) ,pos[i].m_x));
        // vao->setVertexAttributePointer(2, 3, GL_FLOAT, 0, 0);
        // vao->setNumIndices(0);

        uint8_t blockTextureComponent = BlockTextureComponent::getTextureID(BlockTextureComponent::s_registeredTextures[i + 1]);

        // clear the screen and depth buffer
        glBindTexture(GL_TEXTURE_2D, blockTextureComponent);

        // grab an instance of the shader manager

//        ngl::Transformation tx;

        ngl::Mat4 MVP = io_component->m_cameras[0].getVPMatrix();
        ngl::ShaderLib::setUniform("MVP", MVP);

        vao->draw(vaos.size());

        vao->unbind();
    }

}
