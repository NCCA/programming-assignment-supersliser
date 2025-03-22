//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_SYSTEM_H
#define COLONYMANAGER_SYSTEM_H

#include "Component.h"

template<typename T>
class a_System {
public:
    virtual void run(T& i_component) = 0;
};

#endif //COLONYMANAGER_SYSTEM_H
