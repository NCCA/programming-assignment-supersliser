//
// Created by s5605187 on 26/03/25.
//

#include <ngl/Texture.h>
#include "component/BlockTextureComponent.h"

#include "dir.h"
#include "system/ApplyBlockTextureSystem.h"

std::vector<std::string> BlockTextureComponent::s_registeredTextures;



BlockTextureComponent::BlockTextureComponent(size_t i_size)
{

    for (size_t i = 0; i < i_size; i++)
    {
        m_vaos.push_back(nullptr);
        m_textureIDs.push_back(0);
    }
    s_registeredTextures.push_back(fmt::format(DIR, "textures/crate.bmp"));

    ApplyBlockTextureSystem applyBlockTextureSystem;

    applyBlockTextureSystem.i_blockType = BlockType::None;
    applyBlockTextureSystem.run(this, 0);
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