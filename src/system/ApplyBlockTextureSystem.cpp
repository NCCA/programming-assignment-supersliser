//
// Created by s5605187 on 26/03/25.
//

#include "system/ApplyBlockTextureSystem.h"

#include <iostream>

#include "component/BlockComponents.h"
#include "dir.h"
#include "nglExtension/MultiBufferInstanceVAO.h"

void ApplyBlockTextureSystem::run(BlockTextureComponent* io_component, int i_index)
{
    std::string textureDir = DIR;
    std::string textureName = getTextureName(i_blockType);
    std::string path = fmt::format("{}{}", textureDir, textureName);
    int8_t texId = BlockTextureComponent::getTextureID(path);

    // Check if the index is within bounds
    if (i_index >= io_component->m_vaos.size()) {
        std::cerr << "Index out of bounds: " << i_index << std::endl;
        return;
    }

    if (texId != -1)
    {
        io_component->m_vaos[i_index] = io_component->s_trueVaos[texId];
        io_component->m_textureIDs[i_index] = texId;
    }
    else
    {
        BlockTextureComponent::s_registeredTextures.push_back(path);
        texId = BlockTextureComponent::getTextureID(path);
        // Check if the VAO is null before resetting
            if (!io_component->m_vaos[i_index]) {
                auto temp = ngl::vaoFactoryCast<MultiBufferInstanceVAO>(ngl::VAOFactory::createVAO("MultiBufferInstanceVAO", GL_TRIANGLES));
                io_component->m_vaos[i_index] = std::move(temp);
            }

            io_component->m_vaos[i_index]->bind();

            std::array<ngl::Vec3, 36> vertices = BlockComponents::getVertices();

            io_component->m_vaos[i_index]->setData(ngl::MultiBufferVAO::VertexData(sizeof(vertices), vertices[0].m_x));
            io_component->m_vaos[i_index]->setVertexAttributePointer(0, 3, GL_FLOAT, 0, 0);
            io_component->m_vaos[i_index]->setNumIndices(vertices.size());

            ngl::Texture tex;
            tex.loadImage(path);
            io_component->m_textureIDs[i_index] = tex.setTextureGL();


            std::array<ngl::Vec2, 36> texCoords = BlockComponents::getTexCoordinates();

            io_component->m_vaos[i_index]->setData(ngl::MultiBufferVAO::VertexData(sizeof(texCoords), texCoords[0].m_x));
            io_component->m_vaos[i_index]->setVertexAttributePointer(1, 2, GL_FLOAT, 0, 0);
            io_component->m_vaos[i_index]->setNumIndices(texCoords.size());

            io_component->m_vaos[i_index]->unbind();
        io_component->s_trueVaos.push_back(io_component->m_vaos[i_index]);
        // io_component->updateRegisteredTextures(path);

    }
}
