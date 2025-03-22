//
// Created by s5605187 on 21/03/25.
//

#ifndef TABLE_H
#define TABLE_H
#include <cstdint>
#include <vector>
#include "Component.h"
#include "System.h"

using Entity = uint32_t;

const Entity MAX_ENTITIES = 5000;

class Table {

protected:
    std::vector<std::vector<a_Component>> m_columns;

public:
    Table() = default;
    ~Table() = default;

    template<typename T>
    void registerComponentType(const T& i_componentType);

    template<typename T>
    void addComponent(const T& i_component, Entity i_entity);

    template<typename T>
    void removeComponent(Entity i_entity, const T& i_componentType);

    void run(a_System& i_system, uint32_t i_componentID);

    Entity createEntity();
};


#endif //TABLE_H
