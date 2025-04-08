//
// Created by thoma on 22/03/2025.
//

#include "system/SetPositionSystem.h"

void SetPositionSystem::run(TransformComponents* io_component, int i_index)
{
    io_component->m_ps[i_index].m_x = i_pos.m_x;
    io_component->m_ps[i_index].m_y = i_pos.m_y;
    io_component->m_ps[i_index].m_z = i_pos.m_z;
    ngl::ShaderLib::use("TextureShader");
    if ((*i_vaos)[i_index] == nullptr)
    {
        return;
    }
    (*i_vaos)[i_index]->bind();
    (*i_vaos)[i_index]->setData(ngl::AbstractVAO::VertexData(sizeof(io_component->m_ps[i_index]), io_component->m_ps[i_index].m_x), (*i_vaos)[i_index]->getBufferID(2));
    (*i_vaos)[i_index]->setVertexAttributePointer(2, 3, GL_FLOAT, 0, 0);
    (*i_vaos)[i_index]->setNumIndices(3);
    glVertexAttribDivisor(2, 1);
    (*i_vaos)[i_index]->unbind();
}
