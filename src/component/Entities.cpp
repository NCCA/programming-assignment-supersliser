//
// Created by thoma on 22/03/2025.
//

#include "component/Entities.h"

void Entities::addEntity()
{
    int elements = m_entities.size();
    m_entities.push_back(elements);
}

uint32_t Entities::getEntityID(int i_index)
{
    return m_entities[i_index];
}

int Entities::getEntityIndex(uint32_t i_componentID)
{
    for (int i = 0; i < m_entities.size(); i++)
    {
        if (m_entities[i] == i_componentID)
        {
            return i;
        }
    }
    return -1;
}

void Entities::removeEntity(uint32_t i_componentID)
{
    for (int i = 0; i < m_entities.size(); i++)
    {
        if (m_entities[i] == i_componentID)
        {
            m_entities.erase(m_entities.begin() + i);
        }
    }
}

size_t Entities::getEntityCount()
{
    return m_entities.size();
}

Entities::Entities(const size_t i_size)
{
    for (size_t i = 0; i < i_size; i++)
    {
        m_entities.push_back(i);
    }
}
