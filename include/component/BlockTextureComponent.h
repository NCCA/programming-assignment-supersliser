//
// Created by s5605187 on 26/03/25.
//

#ifndef COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H
#define COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H

#include <ngl/AbstractVAO.h>
#include <ngl/Texture.h>

/// @class BlockTextureComponent include/component/BlockTextureComponent.h
/// @brief This class is responsible for managing the textures of blocks in the game as well as data needed to display them.
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-26
class BlockTextureComponent
{
public:
    /// @brief Constructor
    /// @param[in] i_size number of entities in parent table
    BlockTextureComponent(size_t i_size);
    /// @brief utility function to add additional entities after instanciation
    void addBlock();
    /// @brief Default Destructor
    ~BlockTextureComponent();
    /// @brief Static function to get the component ID
    /// @return component ID: 5
    static std::uint8_t getComponentID() { return 5; }
    /// @brief Pointer to the Mesh VBO ID
    /// @detail This is a pointer due to the fact that all blocks are instances of this base block and thus all share an identical mesh VBO with a different transformation matrix and texture index applied at shader level.
    std::shared_ptr<GLuint> m_meshVboId;
    /// @brief Pointer to the UV VBO ID
    /// @detail This is a pointer due to the fact that all blocks are instances of this base block and thus all share an identical UV VBO.
    std::shared_ptr<GLuint> m_uvVboId;
    /// @brief Pointer to the texture VBO ID
    /// @detail This is a pointer to the id of the VBO where m_textureIDs are actually stored.
    std::shared_ptr<GLuint> m_texVboId;
    /// @brief vector of texture IDs
    /// @detail Each index of this vector is a separate entity, these should be updated on the GPU for shader access whenever the vector is updated.
    std::vector<GLfloat> m_textureIDs;
    /// @brief Static Pointer to the VAO ID
    /// @detail Due to the instanced nature of this system, the VAO ID is static and shared between all instances of this class so that all blocks are added to the same VAO as instances.
    std::shared_ptr<GLuint> m_vaoID;

    // @brief Static Vector of the currently active texture paths
    static std::vector<std::string> s_registeredTextures;
    /// @brief Static Vector of the currently active texture IDs
    static std::vector<GLuint> s_registeredTextureIDs;
    /// @brief Static function to load all pre-defined textures
    /// @detail This function loads all the textures that are pre-defined in the game. It is called once at the start of the game to load all the textures into the shader before rendering to speed it up during runtime.
    static void loadAllTextures();
};

#endif //COLONYMANAGERBUILD_BLOCKTEXTURECOMPONENT_H
