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

    std::vector<uint8_t> texs =
        (static_cast<BlockTextureComponent*>(i_world->getColumn(i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get()))->m_textureIDs;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    std::vector<ngl::Vec3> pos = static_cast<TransformComponents*>(i_world->getColumn(i_world->getComponentIndex(TransformComponents::getComponentID())).get())->m_ps;

    std::shared_ptr<GLuint> meshVboId =
        static_cast<BlockTextureComponent*>(i_world->getColumn(i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_meshVboId;
        ngl::ShaderLib::use("TextureShader");

        glBindBuffer(GL_ARRAY_BUFFER, *meshVboId);

        ngl::Mat4 MVP = io_component->m_cameras[0].getVPMatrix();
        ngl::ShaderLib::setUniform("MVP", MVP);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, pos.size());

        glBindBuffer(GL_ARRAY_BUFFER, 0);

}
