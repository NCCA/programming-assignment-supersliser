//
// Created by tom on 3/21/25.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <bitset>

using Entity = std::uint32_t;

const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif //ENTITY_H
