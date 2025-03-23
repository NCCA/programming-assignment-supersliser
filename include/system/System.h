//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_SYSTEM_H
#define COLONYMANAGER_SYSTEM_H


#include <vector>
#include <cstdint>
#include <memory>

template<typename T>
class a_System {
public:
    virtual ~a_System() = default;
    virtual void run(T* io_component, int i_index, void* i_world, std::vector<float> i_args) = 0;
};

#endif //COLONYMANAGER_SYSTEM_H
