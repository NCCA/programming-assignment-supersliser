//
// Created by s5605187 on 26/03/25.
//

#ifndef COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H
#define COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H

#include <ngl/AbstractVAO.h>
#include <ngl/Texture.h>

class BlockTextureComponent
{
public:
    BlockTextureComponent(size_t i_size);
    ~BlockTextureComponent();
    static std::uint8_t getComponentID() { return 5; }
    std::vector<std::shared_ptr<ngl::AbstractVAO>> m_vaos;
    std::vector<uint8_t> m_textureIDs;
    std::vector<GLuint> m_GLTextureIDs;

    static uint8_t getTextureID(std::string_view i_path);
    static std::vector<std::string_view> s_registeredTextures;
};

#endif //COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H
