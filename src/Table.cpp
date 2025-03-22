//
// Created by s5605187 on 22/03/25.
//

#include "Table.h"

uint32_t Table::createEntity() {
    if (m_columns.empty()) {
        m_columns.push_back(std::vector<a_Component *>());
        m_columns[0].push_back(new Entity());
        return 0;
    }
    std::vector<a_Component *> empty = std::vector<a_Component *>(m_columns[0].size());
    Entity entity;
    empty[0] = &entity;
    m_columns.push_back(empty);
    return m_columns.size() - 1;
}

//template<typename T>
//void Table::run(a_System<T>& i_system, uint32_t i_componentID) {
//    for (size_t i = 0; i < m_columns[i_componentID].size(); i++) {
//        i_system.run(m_columns[i_componentID][i]);
//    }
//}

template<typename T>
void Table::removeComponent(uint32_t i_entity, const T& i_componentType)  {
    m_columns[i_entity].erase(i_componentType);
}

uint32_t Table::registerComponentType(a_Component* i_componentType) {
    for (size_t i = 0; i < m_columns[0].size(); i++) {
        if (m_columns[0][i]->getComponentID() == i_componentType->getComponentID()) {
            return i;
        }
    }
    for (size_t i = 0; i < m_columns.size(); i++) {
        m_columns[i].push_back(i_componentType);
    }
    return m_columns[0].size() - 1;
}

void Table::addComponent(a_Component* i_component, uint32_t i_entity){
    uint32_t index = registerComponentType(i_component);
    m_columns[i_entity][index] = i_component;
}



std::vector<a_Component*> Table::getEntity(uint32_t i_entity) const {
    return m_columns[i_entity];
}

int Table::getComponentIndex(uint32_t i_componentID) {
    for (size_t j = 0; j < m_columns.size(); j++) {
        for (size_t i = 0; i < m_columns[j].size(); i++) {
            if (m_columns[j][i]->getComponentID() == i_componentID) {
                return i;
            }
        }
    }
    return -1;
}