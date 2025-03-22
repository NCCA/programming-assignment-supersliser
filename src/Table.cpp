//
// Created by s5605187 on 22/03/25.
//

#include "Table.h"

Entity Table::createEntity() {
    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        if (m_columns[i].empty()) {
            return i;
        }
    }
    if (m_columns.size() < MAX_ENTITIES) {
        m_columns.push_back(std::vector<a_Component>(m_columns[0].size()));
        return m_columns.size() - 1;
    }
    return MAX_ENTITIES;
}

void Table::run(a_System& i_system, uint32_t i_componentID) {
    for (size_t i = 0; i < m_columns[i_componentID].size(); i++) {
        i_system.run(m_columns[i_componentID][i]);
    }
}

template<typename T>
void Table::removeComponent(Entity i_entity, const T& i_componentType)  {
    m_columns[i_entity].erase(i_componentType);
}

template<typename T>
void Table::addComponent(const T& i_component, Entity i_entity){
    m_columns[i_entity].push_back(i_component);
}

template<typename T>
void Table::registerComponentType(const T& i_componentType) {
    m_columns.push_back(Column<T>());
}