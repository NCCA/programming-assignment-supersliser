//
// Created by s5605187 on 21/03/25.
//

#ifndef COLONYMANAGER_COMPONENT_H
#define COLONYMANAGER_COMPONENT_H

#include <cstdint>

class a_Component {
public:
    std::uint32_t m_ComponentID;
    virtual ~a_Component() = default;
};
#endif //COLONYMANAGER_COMPONENT_H
