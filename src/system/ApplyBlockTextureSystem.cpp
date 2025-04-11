//
// Created by s5605187 on 26/03/25.
//

#include <ngl/ShaderLib.h>
#include <iostream>

#include "system/ApplyBlockTextureSystem.h"

void ApplyBlockTextureSystem::run(BlockTextureComponent* io_component, int i_index)
{
    auto textureUnit = static_cast<GLuint>(i_blockType);
    io_component->m_textureIDs[i_index] = textureUnit;

    glBindVertexArray(*io_component->s_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, *io_component->m_texVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * io_component->m_textureIDs.size(), io_component->m_textureIDs.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribDivisor(3, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error applying texture: " << error << std::endl;
    }
}
