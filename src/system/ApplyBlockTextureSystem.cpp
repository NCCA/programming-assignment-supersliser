//
// Created by s5605187 on 26/03/25.
//

#include "system/ApplyBlockTextureSystem.h"
#include <ngl/ShaderLib.h>

#include <iostream>

#include "component/BlockComponents.h"
#include "dir.h"

void ApplyBlockTextureSystem::run(BlockTextureComponent* io_component, int i_index)
{
    // Use i_blockType directly as the texture unit index (0-6)
    auto textureUnit = static_cast<GLuint>(i_blockType);
    io_component->m_textureIDs[i_index] = textureUnit;

    glBindVertexArray(*io_component->s_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, *io_component->m_texVboId);
    glBufferData(GL_ARRAY_BUFFER, io_component->m_textureIDs.size() * sizeof(GLuint), &io_component->m_textureIDs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error applying texture: " << error << std::endl;
    }
    std::cout << "Block " << i_index << " assigned texture ID: " << textureUnit << std::endl;
}
