//
// Created by thoma on 23/03/2025.
//

#ifndef BLOCKCOMPONENT_H
#define BLOCKCOMPONENT_H

#include <ngl/Texture.h>

class BlockComponent
{
public:
    BlockComponent(size_t i_size);
    std::vector<ngl::Texture> m_textures;
    static std::uint8_t getComponentID() { return 3; }
};

#endif //BLOCKCOMPONENT_H
