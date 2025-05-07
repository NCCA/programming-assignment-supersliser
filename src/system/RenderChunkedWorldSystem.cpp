//
// Created by s5605187 on 07/05/25.
//

#include "system/RenderChunkedWorldSystem.h"
#include "component/BlockTextureComponent.h"
#include "component/TransformComponents.h"

void RenderChunkedWorldSystem::run(CameraComponents *io_component, int i_index)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &chunk : *i_chunkedWorld)
    {
        auto textureComponent = static_cast<BlockTextureComponent *>(chunk.getColumn(chunk.getComponentIndex(BlockTextureComponent::getComponentID())).get());

        std::vector<ngl::Vec3> pos = static_cast<TransformComponents *>(chunk.getColumn(chunk.getComponentIndex(TransformComponents::getComponentID())).get())->m_ps;

        std::shared_ptr<GLuint> VAOID =
                static_cast<BlockTextureComponent*>(chunk.getColumn(
                        chunk.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaoID;
        std::shared_ptr<GLuint> meshVboId = static_cast<BlockTextureComponent *>(chunk.getColumn(chunk.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_meshVboId;
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
        glBindVertexArray(*VAOID);

        glBindBuffer(GL_ARRAY_BUFFER, *textureComponent->m_texVboId);
        glBufferData(GL_ARRAY_BUFFER, textureComponent->m_textureIDs.size() * sizeof(GLfloat),
                     textureComponent->m_textureIDs.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
        glVertexAttribDivisor(3, 1);

        ngl::Mat4 MVP = io_component->m_cameras[0].getVPMatrix();
        ngl::ShaderLib::setUniform("MVP", MVP);

        // Draw the meshes with instances
        glDrawArraysInstanced(GL_TRIANGLES, 0, 36, pos.size());

        glBindVertexArray(0);
    }
}