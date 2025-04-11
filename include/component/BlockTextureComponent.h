//
// Created by s5605187 on 26/03/25.
//

#ifndef COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H
#define COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H

#include <ngl/AbstractVAO.h>
#include <ngl/Texture.h>

class BlockTextureComponent
{
    // void setupDefaultBlock(int i_index);
public:
    BlockTextureComponent(size_t i_size);
    void addBlock();
    ~BlockTextureComponent();
    static std::uint8_t getComponentID() { return 5; }
    std::shared_ptr<GLuint> m_meshVboId;
    std::shared_ptr<GLuint> m_uvVboId;
    std::shared_ptr<GLuint> m_texVboId;
    std::vector<GLuint> m_textureIDs;
    static std::shared_ptr<GLuint> s_vaoID;

    static std::vector<std::string> s_registeredTextures;
    static std::vector<GLuint> s_registeredTextureIDs;
    static void loadAllTextures();
};

#endif //COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H
