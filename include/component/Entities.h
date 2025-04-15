//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_ENTITY_H
#define COLONYMANAGER_ENTITY_H
#include <cstdint>
#include <vector>

/// @class Entities include/component/Entities.h
/// @brief Class to store components to define entities.
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-22
class Entities {
  /// @brief Vector of entity IDs
  /// @detail Each index of the vector corresponds to a separate entity
  /// @note The ID of an entity is its index in the vector when it was created
std::vector<uint32_t> m_entities = {};

public:
    /// @brief Static function to get the component ID
    /// @return component ID: 1
    static std::uint8_t getComponentID() { return 1;}

    /// @brief Add an entity to the vector
    void addEntity();

    /// @brief Get the ID of an entity
    /// @param[in] i_index index of the entity
    /// @return ID of the entity
    uint32_t getEntityID(int i_index);

    /// @brief Get the index of an entity
    /// @param[in] i_EntityID ID of the entity
    /// @return index of the entity
    int getEntityIndex(uint32_t i_EntityID);

    /// @brief Remove an entity from the vector
    /// @param[in] i_EntityID ID of the entity
    void removeEntity(uint32_t i_EntityID);

    /// @brief Get the number of entities in the vector
    /// @return number of entities
    size_t getEntityCount();

    /// @brief Default constructor
    Entities() = default;
    /// @brief Constructor
    /// @param[in] i_size number of entities in parent table
    Entities(const size_t i_size);
};

#endif //COLONYMANAGER_ENTITY_H
