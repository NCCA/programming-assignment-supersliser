//
// Created by s5605187 on 21/03/25.
//

#ifndef TABLE_H
#define TABLE_H
#include <cstdint>
#include <utility>
#include <vector>
#include <stdexcept>
#include "Component.h"
#include "System.h"
#include "Entity.h"
#include <set>


class Table {

protected:
    std::vector<std::vector<a_Component*>> m_columns;

public:
    Table() = default;
    ~Table() = default;

    uint32_t registerComponentType(a_Component* i_componentType);

    void addComponent(a_Component* i_component, uint32_t i_entity);

    template<typename T>
    void removeComponent(uint32_t i_entity, const T& i_componentType);

    template<typename T>
    void run(a_System<T>& i_system, uint32_t i_componentID);

    std::vector<a_Component*> getEntity(uint32_t i_entity) const;

    int getComponentIndex(uint32_t i_componentID);

    uint32_t createEntity();
};

template<typename T>
void Table::run(a_System<T>& i_system, uint32_t i_componentID) {
    int index = getComponentIndex(std::move(i_componentID));
    for (auto & m_column : m_columns) {
        i_system.run(static_cast<T&>((*m_column[index])));
    }
}


#endif //TABLE_H
