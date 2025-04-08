//
// Created by thoma on 07/04/2025.
//

#include "nglExtension/MultiBufferInstanceVAO.h"

#include <iostream>

void MultiBufferInstanceVAO::draw() const
{
    if(m_allocated == false)
    {
        std::cerr<<"Warning trying to draw an unallocated VOA\n";
    }
    if(m_bound == false)
    {
        std::cerr<<"Warning trying to draw an unbound VOA\n";
    }
    glDrawElements(m_mode,static_cast<GLsizei>(m_indicesCount),GL_FLOAT,static_cast<ngl::Real *>(nullptr));
}


void MultiBufferInstanceVAO::draw(int i_instanceCount) const
{
    if(m_allocated == false)
    {
        std::cerr<<"Warning trying to draw an unallocated VOA\n";
    }
    if(m_bound == false)
    {
        std::cerr<<"Warning trying to draw an unbound VOA\n";
    }
    glDrawElementsInstanced(m_mode,static_cast<GLsizei>(m_indicesCount),GL_UNSIGNED_INT,0, i_instanceCount);
}

void MultiBufferInstanceVAO::setData(const VertexData &_data)
{

    if(m_bound == false)
    {
        std::cerr<<"trying to set VOA data when unbound\n";
    }
    GLuint vboID;
    glGenBuffers(1, &vboID);
    m_vboIDs.push_back(vboID);
    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(_data.m_size), &_data.m_data, _data.m_mode);

    m_allocated=true;
}

void MultiBufferInstanceVAO::setData(const VertexData &_data, GLuint i_vboID)
{

    if(m_bound == false)
    {
        std::cerr<<"trying to set VOA data when unbound\n";
    }
    if (i_vboID != 255)
    {
        glGenBuffers(1, &i_vboID);
    }

    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, i_vboID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(_data.m_size), &_data.m_data, _data.m_mode);

    m_allocated=true;
}

GLuint MultiBufferInstanceVAO::getBufferID(GLuint i_vboID) const
{
    if (i_vboID > m_vboIDs.size() - 1 || m_vboIDs.empty())
    {
        return 255;
    }
    return m_vboIDs[i_vboID];
}