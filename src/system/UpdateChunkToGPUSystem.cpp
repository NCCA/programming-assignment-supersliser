//
// Created by s5605187 on 07/05/25.
//

#include <iostream>
#include "system/UpdateChunkToGPUSystem.h"
#include "component/BlockTextureComponent.h"
#include "component/TransformComponents.h"

void UpdateChunkToGPUSystem::run(ChunkComponent *io_component, int i_index) {
        if (io_component->m_loaded[0]) {
            auto chunk = (*i_world)[i_index];
            auto blockTextureComponent = static_cast<BlockTextureComponent*>(chunk.getColumn(chunk.getComponentIndex(BlockTextureComponent::getComponentID())).get());
            auto transformComponent = static_cast<TransformComponents*>(chunk.getColumn(chunk.getComponentIndex(TransformComponents::getComponentID())).get());

            // Add the texture to the VBO
            glBindVertexArray(*blockTextureComponent->m_vaoID);
            glBindBuffer(GL_ARRAY_BUFFER, *blockTextureComponent->m_texVboId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * blockTextureComponent->m_textureIDs.size(), blockTextureComponent->m_textureIDs.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
            glVertexAttribDivisor(3, 1);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            // Add the Instanced Position VBO
            glBindVertexArray(*blockTextureComponent->m_vaoID);

            glGenBuffers(1, transformComponent->m_positionVboId.get());
            glBindBuffer(GL_ARRAY_BUFFER, *transformComponent->m_positionVboId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(ngl::Vec3) * transformComponent->m_ps.size(), &transformComponent->m_ps[0].m_x, GL_STATIC_DRAW);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glVertexAttribDivisor(2, 1);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            auto error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cerr << "Error applying texture: " << error << std::endl;
            }
        }
    
}