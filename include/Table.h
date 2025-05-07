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

/// @class Table include/Table.h
/// @brief The Table class is a container for managing entities and their associated components.
/// It provides functionality to register component types, run systems on components, and manage entities.
/// @author Thomas Lower
/// @date 2023-03-25
/// @version 1.0
class Table {

protected:
    /// @brief A vector of columns, each column is a component type.
    std::vector<Column> m_columns = {};

public:
  /// @brief Default constructor
    Table() = default;
    /// @brief Destructor
    ~Table();

    /// @brief Registers a component type and returns its index.
    /// @param i_componentType The component type to register.
    /// @return The index of the registered component type.
    /// @throws std::invalid_argument if the component type is already registered.
    uint32_t registerComponentType(const uint8_t i_componentType);

    /// @brief Runs a system on a specific component type.
    /// @tparam T The type of the component.
    /// @param i_system The system to run.
    /// @param i_componentType The component type to run the system on.
    /// @param startIndex The inclusive starting index for the system run (default is -1).
    /// @param endIndex The exclusive ending index for the system run (default is -1).
    /// @throws std::invalid_argument if the component type is not found.
    /// @throws std::runtime_error if the component is null.
    /// @detail A subset of entities can be specified using the startIndex and endIndex params. If these are ommited, the system will be run on every component of that type in the table. If startindex = endindex, then the system will only be run on the entity specified by startindex.
    template<typename T>
    void run(a_System<T>* i_system, const uint8_t i_componentType, int i_startIndex = -1, int i_endIndex = -1);

    /// @brief gets the index of a component type.
    /// @param i_componentType The component type to get the index of.
    /// @return The index of the component type.
    int getComponentIndex(uint8_t i_componentType) const;

    /// @gets a pointer to a column of a specific component type.
    /// @param i_componentType The component type to get the column of.
    /// @return A shared pointer to the column of the component type.
    /// @throws std::invalid_argument if the component type is not found.
    std::shared_ptr<void> getColumn(uint32_t i_columnIndex) const;

    /// @brief Gets the number of component types registered in the table.
    /// @return The number of component types.
    unsigned int getComponentCount() const;

    /// @brief Gets the number of entities in the table.
    /// @return The number of entities.
    unsigned int getEntityCount() const;

    /// @brief Creates a new entity and returns its ID.
    /// @return The ID of the created entity.
    uint32_t createEntity();

};

template<typename T>
void Table::run(a_System<T>* i_system, const uint8_t i_componentType, int i_startIndex, int i_endIndex) {
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
