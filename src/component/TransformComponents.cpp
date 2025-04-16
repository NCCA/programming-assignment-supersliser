//
// Created by thoma on 22/03/2025.
//

#include <iostream>
#include <ngl/VAOFactory.h>

#include "component/BlockTextureComponent.h"
#include "component/TransformComponents.h"

TransformComponents::TransformComponents(size_t i_size)
{
    if (*BlockTextureComponent::s_vaoID == 0)
    {
        for (size_t i = 0; i < i_size; i++)
        {
            m_ps.push_back(ngl::Vec3(0, 0, 0));
        }
        return;
    }
    m_positionVboId = std::make_shared<GLuint>();

    // Add the Instanced Position VBO
    glBindVertexArray(*BlockTextureComponent::s_vaoID);
    for (size_t i = 0; i < i_size; i++)
    {
        m_ps.push_back(ngl::Vec3(0, 0, 0));
    }
    glGenBuffers(1, m_positionVboId.get());
    glBindBuffer(GL_ARRAY_BUFFER, *m_positionVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ngl::Vec3) * m_ps.size(), &m_ps[0].m_x, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribDivisor(2, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error applying position: " << error << std::endl;
    }
}

void TransformComponents::addEntity()
{
    m_ps.push_back(ngl::Vec3(0, 0, 0));
    if (*BlockTextureComponent::s_vaoID == 0)
    {
        return;
    }

    // Update the Instanced Position VBO
    glBindVertexArray(*BlockTextureComponent::s_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, *m_positionVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ngl::Vec3) * m_ps.size(), &m_ps[0].m_x, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error applying position: " << error << std::endl;
    }
}
