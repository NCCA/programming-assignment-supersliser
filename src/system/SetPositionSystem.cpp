//
// Created by thoma on 22/03/2025.
//

#include "system/SetPositionSystem.h"


void SetPositionSystem::run(TransformComponents* io_component, int i_index)
{
    io_component->m_ps[i_index].m_x = i_pos.m_x;
    io_component->m_ps[i_index].m_y = i_pos.m_y;
    io_component->m_ps[i_index].m_z = i_pos.m_z;
    glBindVertexArray(*BlockTextureComponent::s_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, *io_component->m_positionVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ngl::Vec3) * io_component->m_ps.size(), &io_component->m_ps[0].m_x, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error applying position: " << error << std::endl;
    }
}
