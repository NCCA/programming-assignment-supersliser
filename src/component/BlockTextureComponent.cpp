//
// Created by s5605187 on 26/03/25.
//

#include <ngl/Texture.h>
#include "component/BlockTextureComponent.h"

#include "dir.h"
#include "component/BlockComponents.h"
#include "nglExtension/MultiBufferInstanceVAO.h"
#include "system/ApplyBlockTextureSystem.h"

std::vector<std::string> BlockTextureComponent::s_registeredTextures;
std::vector<std::shared_ptr<MultiBufferInstanceVAO>> BlockTextureComponent::s_trueVaos;



BlockTextureComponent::BlockTextureComponent(size_t i_size)
{

    for (size_t i = 0; i < i_size; i++)
    {
        m_vaos.push_back(nullptr);
        m_textureIDs.push_back(0);
    }
    s_registeredTextures.push_back(fmt::format(DIR, "textures/crate.bmp"));
    for (size_t i = 0; i < i_size; i++)
    {
        setupDefaultBlock(i);
    }
}

void BlockTextureComponent::addBlock()
{
    m_vaos.push_back(nullptr);
    m_textureIDs.push_back(0);
    setupDefaultBlock(m_vaos.size() -1);
}

int8_t BlockTextureComponent::getTextureID(const std::string& i_path)
{
    for (size_t i = 0; i < s_registeredTextures.size(); i++)
    {
        if (s_registeredTextures[i] == i_path)
        {
            return i;
        }
    }
    return -1;
}

BlockTextureComponent::~BlockTextureComponent()
{
    for (size_t i = 0; i < m_vaos.size(); i++)
    {
        if (m_vaos[i] != nullptr)
        {
            m_vaos[i]->removeVAO();
        }
    }
    m_textureIDs.clear();
    m_vaos.clear();
    s_registeredTextures.clear();
}

void BlockTextureComponent::setupDefaultBlock(int i_index)
{
    std::string textureDir = DIR;
    std::string textureName = ApplyBlockTextureSystem::getTextureName(BlockType::None);
    std::string path = fmt::format("{}{}", textureDir, textureName);
    int8_t texId = getTextureID(path);

    if (texId != -1)
    {
                m_vaos[i_index] = s_trueVaos[texId];
                m_textureIDs[i_index] = texId;
    }
    else
    {
        BlockTextureComponent::s_registeredTextures.push_back(path);

        texId = BlockTextureComponent::getTextureID(path);
        // Check if the VAO is null before resetting
            if (!m_vaos[i_index]) {
                auto temp = ngl::vaoFactoryCast<MultiBufferInstanceVAO>(ngl::VAOFactory::createVAO("MultiBufferInstanceVAO", GL_TRIANGLES));
                m_vaos[i_index] = std::move(temp);
            }

            m_vaos[i_index]->bind();

            std::array<ngl::Vec3, 36> vertices = BlockComponents::getVertices();

            m_vaos[i_index]->setData(ngl::MultiBufferVAO::VertexData(sizeof(vertices), vertices[0].m_x));
            m_vaos[i_index]->setVertexAttributePointer(0, 3, GL_FLOAT, 0, 0);
            m_vaos[i_index]->setNumIndices(vertices.size());

            ngl::Texture tex;
            tex.loadImage(path);
            m_textureIDs[i_index] = tex.setTextureGL();


            std::array<ngl::Vec2, 36> texCoords = BlockComponents::getTexCoordinates();

            m_vaos[i_index]->setData(ngl::MultiBufferVAO::VertexData(sizeof(texCoords), texCoords[0].m_x));
            m_vaos[i_index]->setVertexAttributePointer(1, 2, GL_FLOAT, 0, 0);
            m_vaos[i_index]->setNumIndices(texCoords.size());

            m_vaos[i_index]->unbind();

        s_trueVaos.push_back(m_vaos[i_index]);
    }
}