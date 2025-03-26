//
// Created by s5605187 on 26/03/25.
//

#ifndef COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H
#define COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H

#include <ngl/Texture.h>

class BlockTextureComponent
{
public:
    BlockTextureComponent(size_t i_size);
    static std::uint8_t getComponentID() { return 5; }
    std::vector<GLuint> m_textures;
};

#endif //COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H
