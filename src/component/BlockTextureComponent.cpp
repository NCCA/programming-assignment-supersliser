//
// Created by s5605187 on 26/03/25.
//

#include <ngl/Texture.h>
#include "component/BlockTextureComponent.h"

#include <iostream>

#include "dir.h"
#include "component/BlockComponents.h"
#include "system/ApplyBlockTextureSystem.h"

std::vector<std::string> BlockTextureComponent::s_registeredTextures;
std::vector<std::shared_ptr<GLuint>> BlockTextureComponent::s_trueVbos;
std::shared_ptr<GLuint> BlockTextureComponent::s_vaoID = std::make_shared<GLuint>();


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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenBuffers(1, m_uvVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_uvVboId);
    auto texCoords = BlockComponents::getTexCoordinates();
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(texCoords)), &texCoords[0].m_x, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for (size_t i = 0; i < i_size; i++)
    {
        m_textureIDs.push_back(0);
    }
    s_registeredTextures.push_back(fmt::format(DIR, "textures/crate.bmp"));
    m_texVboId = std::make_shared<GLuint>();
    glGenBuffers(1, m_texVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glBufferData(GL_ARRAY_BUFFER, m_textureIDs.size(), &m_textureIDs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);
    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error Creating texture component: " << error << std::endl;
    }
}

void BlockTextureComponent::addBlock()
{
    m_textureIDs.push_back(0);
    glBindVertexArray(*s_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, *m_texVboId);
    glBufferData(GL_ARRAY_BUFFER, m_textureIDs.size(), &m_textureIDs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error adding block: " << error << std::endl;
    }
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
    m_textureIDs.clear();
    m_meshVboId.reset();
    m_uvVboId.reset();
    s_registeredTextures.clear();
}