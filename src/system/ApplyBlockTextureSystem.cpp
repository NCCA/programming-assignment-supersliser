//
// Created by s5605187 on 26/03/25.
//

#include "system/ApplyBlockTextureSystem.h"

#include <iostream>

#include "component/BlockComponents.h"

void ApplyBlockTextureSystem::run(BlockTextureComponent* io_component, int i_index)
{
    std::string_view path = i_texturePath;
    uint8_t texId = io_component->getTextureID(path);

    // Check if the index is within bounds
    if (i_index >= io_component->m_vaos.size()) {
        std::cerr << "Index out of bounds: " << i_index << std::endl;
        return;
    }

    if (texId == io_component->s_registeredTextures.size() - 1)
    {
        // Check if the VAO is null before resetting
        if (!io_component->m_vaos[i_index]) {
            auto temp = ngl::VAOFactory::createVAO(ngl::multiBufferVAO, GL_TRIANGLES);
            io_component->m_vaos[i_index] = std::move(temp);
        }

        // io_component->m_vaos[i_index].reset((ngl::VAOFactory::createVAO(ngl::multiBufferVAO, GL_TRIANGLES).get()));
        io_component->m_vaos[i_index]->bind();

        std::array<ngl::Vec3, 36> vertices = BlockComponents::getVertices();

        io_component->m_vaos[i_index]->setData(ngl::MultiBufferVAO::VertexData(sizeof(vertices), vertices[0].m_x));
        io_component->m_vaos[i_index]->setVertexAttributePointer(0, 3, GL_FLOAT, 0, 0);
        io_component->m_vaos[i_index]->setNumIndices(vertices.size());

        ngl::Texture tex;
        tex.loadImage(path);
        io_component->m_textureIDs[i_index] = texId;
        io_component->m_GLTextureIDs.push_back(tex.setTextureGL());


        io_component->m_vaos[i_index]->unbind();
    }
    else
    {
        io_component->m_vaos[i_index] = io_component->m_vaos[texId];
        io_component->m_textureIDs[i_index] = texId;
        io_component->m_GLTextureIDs[i_index] = io_component->m_GLTextureIDs[texId];
    }
}
