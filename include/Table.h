//
// Created by s5605187 on 21/03/25.
//

#ifndef TABLE_H
#define TABLE_H
#include <cstdint>
#include <vector>
#include <stdexcept>
#include "component/Column.h"
#include "system/System.h"
#include "component/Entity.h"


class Table {

protected:
    std::vector<Column> m_columns;

public:
    Table() = default;
    ~Table() = default;

    uint32_t registerComponentType(const uint8_t i_componentType);

    template<typename T>
    void run(a_System<T>& i_system, const uint8_t i_componentType);

    std::vector<Column> getEntity(uint32_t i_entity) const;

    int getComponentIndex(uint8_t i_componentType) const;

    uint32_t createEntity();
};

template<typename T>
void Table::run(a_System<T>& i_system, const uint8_t i_componentType) {
    int index = getComponentIndex(i_componentType);
    if (index == -1) {
        throw std::invalid_argument("Component type not found");
    }
    for (int i = 0; i < static_cast<Entity*>(m_columns[0].m_column)->getEntityCount(); i++) {
        i_system.run(*static_cast<T*>(m_columns[index].m_column), i);
    }
}


#endif //TABLE_H
