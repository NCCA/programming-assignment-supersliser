//
// Created by s5605187 on 21/03/25.
//

#ifndef TABLE_H
#define TABLE_H
#include <cstdint>
#include <memory>
#include <vector>
#include <stdexcept>
#include "component/Column.h"
#include "system/System.h"
#include "component/Entities.h"


class Table {

protected:
    std::vector<Column> m_columns = {};

public:
    Table() = default;
    ~Table();

    uint32_t registerComponentType(const uint8_t i_componentType);

    template<typename T>
    void run(a_System<T>* i_system, const uint8_t i_componentType, int startIndex = -1, int endIndex = -1);

    std::vector<Column> getEntity(uint32_t i_entity) const;

    int getComponentIndex(uint8_t i_componentType) const;

    std::shared_ptr<void> getColumn(uint32_t i_columnIndex) const;

    uint32_t createEntity();
};

template<typename T>
void Table::run(a_System<T>* i_system, const uint8_t i_componentType, int startIndex, int endIndex) {
    int index = getComponentIndex(i_componentType);
    if (index == -1) {
        throw std::invalid_argument("Component type not found");
    }
    if (startIndex == -1)
    {
        startIndex = 0;
    }
    if (endIndex == -1)
    {
        endIndex = static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount();
    }
    if (startIndex == endIndex)
    {
        endIndex++;
    }
    for (int i = startIndex; i < endIndex; i++) {
        T* component = static_cast<T*>(m_columns[index].m_column.get());
        if (component == nullptr) {
            throw std::runtime_error("Component is null");
        }
        i_system->run(component, i);
    }
}
#endif //TABLE_H
