//
// Created by thoma on 24/03/2025.
//

#ifndef RENDERWORLDSYSTEM_H
#define RENDERWORLDSYSTEM_H
#include "System.h"
#include "Table.h"
#include "component/CameraComponents.h"
#include "component/TransformComponents.h"

/// @class RenderWorldSystem include/system/RenderWorldSystem.h
/// @brief System to render the world
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-24
/// @details This system renders the world by using the CameraComponents to store the camera position. It uses the Table class to access the world data.
class RenderWorldSystem : public a_System<CameraComponents>
{
public:
    /// @brief The world table to be rendered
    Table* i_world;
    /// @brief Runs the system
    /// @param[in] io_component A pointer to the CameraComponents to have the world rendered
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_world [Required] The world table to be rendered
    void run(CameraComponents* io_component, int i_index) override;
};
#endif //RENDERWORLDSYSTEM_H
