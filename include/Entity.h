//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_ENTITY_H
#define COLONYMANAGER_ENTITY_H

#include "Component.h"

class Entity : public a_Component {
public:
    std::uint8_t getComponentID() const override { return 1;}
};

#endif //COLONYMANAGER_ENTITY_H
