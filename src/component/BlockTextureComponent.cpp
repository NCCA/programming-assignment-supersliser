//
// Created by s5605187 on 26/03/25.
//

#include <ngl/Texture.h>
#include "component/BlockTextureComponent.h"

BlockTextureComponent::BlockTextureComponent(size_t i_size)
{
    for (size_t i = 0; i < i_size; i++)
    {
        m_textures.push_back(0);
    }
}