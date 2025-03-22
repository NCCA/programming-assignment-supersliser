//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_SYSTEM_H
#define COLONYMANAGER_SYSTEM_H

#include "Component.h"

class a_System {
public:
    virtual ~a_System() = default;
    virtual void run(a_Component& i_component) = 0;
};

#endif //COLONYMANAGER_SYSTEM_H
