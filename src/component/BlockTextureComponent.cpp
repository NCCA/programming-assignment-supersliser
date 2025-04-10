//
// Created by s5605187 on 26/03/25.
//

#include <ngl/Texture.h>
#include "component/BlockTextureComponent.h"

#include <iostream>
#include <ngl/ShaderLib.h>

#include "dir.h"
#include "component/BlockComponents.h"
#include "system/ApplyBlockTextureSystem.h"
#include "utils.h"

std::vector<std::string> BlockTextureComponent::s_registeredTextures;
std::vector<std::shared_ptr<GLuint>> BlockTextureComponent::s_trueVbos;
std::shared_ptr<GLuint> BlockTextureComponent::s_vaoID = std::make_shared<GLuint>();
std::vector<std::shared_ptr<GLuint>> BlockTextureComponent::s_registeredTextureIDs;


BlockTextureComponent::BlockTextureComponent(size_t i_size)
{
    glGenVertexArrays(1, s_vaoID.get());
    glBindVertexArray(*s_vaoID);
    m_meshVboId = std::make_shared<GLuint>();
    m_uvVboId = std::make_shared<GLuint>();
    glGenBuffers(1, m_meshVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_meshVboId);
    auto verts = BlockComponents::getVertices();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(verts)), &verts[0].m_x, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenBuffers(1, m_uvVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_uvVboId);
    auto texCoords = BlockComponents::getTexCoordinates();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(texCoords)), &texCoords[0].m_x, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for (size_t i = 0; i < i_size; i++)
    {
        m_textureIDs.push_back(0);
    }
    s_registeredTextureIDs.clear();
    m_texVboId = std::make_shared<GLuint>();
    glGenBuffers(1, m_texVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glBufferData(GL_ARRAY_BUFFER, m_textureIDs.size() * sizeof(GLuint) + 1, &m_textureIDs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, 0, nullptr);
    glVertexAttribDivisor(3, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error Creating texture component: " << error << std::endl;
    }
    loadAllTextures();
}

void BlockTextureComponent::addBlock()
{
    m_textureIDs.push_back(0);
    glBindVertexArray(*s_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glBufferData(GL_ARRAY_BUFFER, m_textureIDs.size() * sizeof(GLuint), &m_textureIDs[0], GL_STATIC_DRAW);
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
    ngl::ShaderLib::use("TextureShader"); // Ensure the shader program is active

    for (size_t i = 0; i < 7; i++)
    {
        std::string textureDir = DIR;
        std::string textureName = ApplyBlockTextureSystem::getTextureName(static_cast<BlockType>(i));
        std::string path = fmt::format("{}{}", textureDir, textureName);
        s_registeredTextures.push_back(path);

        ngl::Texture tex;
        tex.loadImage(path);
        GLuint texID;
        glGenTextures(1, &texID);

        // Use the loop index i as the texture unit instead
        GLuint textureUnit = i;
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, texID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        auto width = tex.width();
        auto height = tex.height();
        auto data = tex.getPixels();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

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
        s_registeredTextureIDs.push_back(std::make_shared<GLuint>(texID));
    }
}