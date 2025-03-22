//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_ENTITY_H
#define COLONYMANAGER_ENTITY_H
#include <cstdint>
#include <vector>

class Entity {
std::vector<uint32_t> m_entities;

public:
    static std::uint8_t getComponentID() { return 1;}

    void addEntity();

    uint32_t getEntityID(int i_index);

    int getEntityIndex(uint32_t i_EntityID);

    void removeEntity(uint32_t i_EntityID);

    size_t getEntityCount();

};

#endif //COLONYMANAGER_ENTITY_H
