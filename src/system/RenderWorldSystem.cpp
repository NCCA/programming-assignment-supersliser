//
// Created by thoma on 24/03/2025.
//

#include <ngl/Mat4.h>
#include <ngl/MultiBufferVAO.h>
#include <ngl/ShaderLib.h>

#include "component/TransformComponents.h"
#include "component/BlockTextureComponent.h"
#include "system/RenderWorldSystem.h"

void RenderWorldSystem::run(CameraComponents* io_component, int i_index)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto textureComponent = static_cast<BlockTextureComponent*>(
        i_world->getColumn(i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get());

    std::vector<ngl::Vec3> pos = static_cast<TransformComponents*>(i_world->getColumn(
        i_world->getComponentIndex(TransformComponents::getComponentID())).get())->m_ps;

    std::shared_ptr<GLuint> meshVboId =
        static_cast<BlockTextureComponent*>(i_world->getColumn(
            i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_meshVboId;
    ngl::ShaderLib::use("TextureShader");

    for (size_t i = 0; i < BlockTextureComponent::s_registeredTextureIDs.size(); i++)
    {
        std::string nameStr = fmt::format("tex[{}]", i);
        ngl::ShaderLib::setUniform(nameStr, static_cast<int>(i));
    }

    for (size_t i = 0; i < BlockTextureComponent::s_registeredTextureIDs.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, BlockTextureComponent::s_registeredTextureIDs[i]);
    }

    // Bind VAO and VBOs
    glBindVertexArray(*BlockTextureComponent::s_vaoID);

    // THIS IS THE CRITICAL PART - rebinding the texture ID buffer
    glBindBuffer(GL_ARRAY_BUFFER, *textureComponent->m_texVboId);
    // Make sure we're using the latest texture IDs data
    glBufferData(GL_ARRAY_BUFFER, textureComponent->m_textureIDs.size() * sizeof(GLfloat),
                 textureComponent->m_textureIDs.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribDivisor(3, 1);

    ngl::Mat4 MVP = io_component->m_cameras[0].getVPMatrix();
    ngl::ShaderLib::setUniform("MVP", MVP);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, pos.size());

    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error rendering world: " << error << std::endl;
    }
}
