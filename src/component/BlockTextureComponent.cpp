//
// Created by s5605187 on 26/03/25.
//

#include <ngl/Texture.h>
#include <iostream>
#include <ngl/ShaderLib.h>

#include "dir.h"
#include "component/BlockTextureComponent.h"
#include "component/BlockComponents.h"
#include "system/ApplyBlockTextureSystem.h"

// Declare static variables
std::vector<std::string> BlockTextureComponent::s_registeredTextures;
std::shared_ptr<GLuint> BlockTextureComponent::s_vaoID = std::make_shared<GLuint>();
std::vector<GLuint> BlockTextureComponent::s_registeredTextureIDs;

BlockTextureComponent::BlockTextureComponent(size_t i_size)
{
    //Create the VAO
    glGenVertexArrays(1, s_vaoID.get());
    glBindVertexArray(*s_vaoID);

    //Create the Mesh VBO
    m_meshVboId = std::make_shared<GLuint>();
    glGenBuffers(1, m_meshVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_meshVboId);
    auto verts = BlockComponents::getVertices();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(verts)), &verts[0].m_x, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Create the UV VBO
    m_uvVboId = std::make_shared<GLuint>();
    glGenBuffers(1, m_uvVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_uvVboId);
    auto texCoords = BlockComponents::getTexCoordinates();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(texCoords)), &texCoords[0].m_x, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Create the Texture Instance VBO
    for (size_t i = 0; i < i_size; i++)
    {
        m_textureIDs.push_back(0);
    }
    s_registeredTextureIDs.clear();
    m_texVboId = std::make_shared<GLuint>();
    glGenBuffers(1, m_texVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glBufferData(GL_ARRAY_BUFFER, m_textureIDs.size() * sizeof(GLfloat), m_textureIDs.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribDivisor(3, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error Creating texture component: " << error << std::endl;
    }

    //Load all the textures
    loadAllTextures();
}

void BlockTextureComponent::addBlock()
{
    // Resizes the texture VBO
    m_textureIDs.push_back(0);
    glBindVertexArray(*s_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glBufferData(GL_ARRAY_BUFFER, m_textureIDs.size() * sizeof(GLfloat), m_textureIDs.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribDivisor(3, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error adding block: " << error << std::endl;
    }
}

BlockTextureComponent::~BlockTextureComponent()
{
    m_textureIDs.clear();
    m_meshVboId.reset();
    m_uvVboId.reset();
    s_registeredTextures.clear();
}

void BlockTextureComponent::loadAllTextures()
{
    s_registeredTextures.clear();
    ngl::ShaderLib::use("TextureShader");

    for (size_t i = 0; i < 7; i++)
    {
        // Add a path to the texture vector
        std::string textureDir = getDir();
        std::string textureName = ApplyBlockTextureSystem::getTextureName(static_cast<BlockType>(i));
        std::string path = fmt::format("{}{}", textureDir, textureName);
        s_registeredTextures.push_back(path);

        // Load the texture
        ngl::Texture tex;
        tex.loadImage(path);
        GLuint texID;
        glGenTextures(1, &texID);

        // Bind the texture
        GLuint textureUnit = i;
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, texID);

        // Generate the texture mipmap
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Gather Texture Parameters
        auto width = tex.width();
        auto height = tex.height();
        auto data = tex.getPixels();

        // Upload the texture data to the GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Set the texture unit in the shader to the 2DSampler
        std::string nameStr = fmt::format("tex[{}]", textureUnit);
        GLint uniformLocation = glGetUniformLocation(ngl::ShaderLib::getProgramID("TextureShader"), nameStr.c_str());
        if (uniformLocation == -1)
        {
            std::cerr << "T Uniform " << nameStr << " not found in shader program." << std::endl;
        }
        else
        {
            glUniform1i(uniformLocation, textureUnit);
        }
        s_registeredTextureIDs.push_back(texID);
    }
}
