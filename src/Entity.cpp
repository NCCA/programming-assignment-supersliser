//
// Created by thoma on 22/03/2025.
//

#include "Entity.h"


void Entity::addEntity() {
    m_entities.push_back(m_entities.size());
}

uint32_t Entity::getEntityID(int i_index) {
    return m_entities[i_index];
}

int Entity::getEntityIndex(uint32_t i_componentID) {
    for (int i = 0; i < m_entities.size(); i++) {
        if (m_entities[i] == i_componentID) {
            return i;
        }
    }
    return -1;
}

void Entity::removeEntity(uint32_t i_componentID) {
    for (int i = 0; i < m_entities.size(); i++) {
        if (m_entities[i] == i_componentID) {
            m_entities.erase(m_entities.begin() + i);
        }
    }
}

size_t Entity::getEntityCount() {
    return m_entities.size();
}