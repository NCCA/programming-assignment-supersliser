//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_SYSTEM_H
#define COLONYMANAGER_SYSTEM_H


#include <vector>
#include <cstdint>
#include <memory>

/// @class a_System include/system/System.h
/// @brief Abstract base class for all systems in the ECS
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-22
template<typename T>
class a_System {
public:
    /// @brief Default destructor
    virtual ~a_System() = default;
    /// @brief Pure virtual function to run a system
    virtual void run(T* io_component, int i_index) = 0;
};

#endif //COLONYMANAGER_SYSTEM_H
