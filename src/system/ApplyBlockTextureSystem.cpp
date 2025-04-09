//
// Created by s5605187 on 26/03/25.
//

#include "system/ApplyBlockTextureSystem.h"

#include <iostream>

#include "component/BlockComponents.h"
#include "dir.h"

void ApplyBlockTextureSystem::run(BlockTextureComponent* io_component, int i_index)
{
    std::string textureDir = DIR;
    std::string textureName = getTextureName(i_blockType);
    std::string path = fmt::format("{}{}", textureDir, textureName);
    int8_t texId = BlockTextureComponent::getTextureID(path);

    if (texId != -1)
    {
        glBindVertexArray(*io_component->s_vaoID);
        io_component->m_textureIDs[i_index] = texId;
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, *io_component->m_texVboId);
        glBufferData(GL_ARRAY_BUFFER, io_component->m_textureIDs.size(), &io_component->m_textureIDs[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        auto error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "Error applying texture: " << error << std::endl;
        }
    }
    else
    {
        BlockTextureComponent::s_registeredTextures.push_back(path);

            ngl::Texture tex;
            tex.loadImage(path);
            GLuint texID;
        glGenTextures(1, &texID);
        io_component->m_textureIDs[i_index] = texID;
        glActiveTexture(GL_TEXTURE0 + io_component->s_registeredTextures.size() - 1);
        glBindTexture(GL_TEXTURE_2D, io_component->m_textureIDs[i_index]);
        glUniform1i(glGetUniformLocation(io_component->m_textureIDs[i_index], fmt::format("tex{}", io_component->m_textureIDs[i_index]).c_str()), io_component->s_registeredTextures.size());
        glBindBuffer(GL_ARRAY_BUFFER, *io_component->m_texVboId);
        glBufferData(GL_ARRAY_BUFFER, io_component->m_textureIDs.size(), &io_component->m_textureIDs[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        auto error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "Error loading texture: " << error << std::endl;
        }
    }
}
