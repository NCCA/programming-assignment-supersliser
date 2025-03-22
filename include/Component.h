//
// Created by s5605187 on 21/03/25.
//

#ifndef COLONYMANAGER_COMPONENT_H
#define COLONYMANAGER_COMPONENT_H

#include <cstdint>

class a_Component {
public:
    virtual std::uint8_t getComponentID() const { return 0;}
};
#endif //COLONYMANAGER_COMPONENT_H
