//
// Created by s5605187 on 26/03/25.
//

#include <ngl/Texture.h>
#include "component/BlockTextureComponent.h"
std::vector<std::string_view> BlockTextureComponent::s_registeredTextures;



BlockTextureComponent::BlockTextureComponent(size_t i_size)
{

    for (size_t i = 0; i < i_size; i++)
    {
        m_vaos.push_back(nullptr);
        m_textureIDs.push_back(0);
    }
}

uint8_t BlockTextureComponent::getTextureID(std::string_view i_path)
{
    for (size_t i = 0; i < s_registeredTextures.size(); i++)
    {
        if (s_registeredTextures[i] == i_path)
        {
            return i;
        }
    }
    s_registeredTextures.push_back(i_path);
    return s_registeredTextures.size() - 1;
}