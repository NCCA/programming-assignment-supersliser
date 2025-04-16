//
// Created by thoma on 22/03/2025.
//

#ifndef SETPOSITIONSYSTEM_H
#define SETPOSITIONSYSTEM_H

#include "System.h"
#include "Table.h"
#include "component/TransformComponents.h"
#include <ngl/ShaderLib.h>
#include <ngl/AbstractVAO.h>
#include <ngl/MultiBufferVAO.h>
#include "component/BlockTextureComponent.h"

/// @class SetPositionSystem include/system/SetPositionSystem.h
/// @brief System to set the position of a block
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-22
/// @details This system is used to set the position of a block in the world. It uses the TransformComponent to store the position information. When the data is updated here, it is also updated in the shader.
class SetPositionSystem : public a_System<TransformComponents>
{
public:
  /// @brief The position to be set when the system is run
    ngl::Vec3 i_pos;
    /// @brief runs the system
    /// @param[in] io_component A pointer to the TransformComponent to have the position set
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_pos [Required] The position to be set
    void run(TransformComponents* io_component, int i_index) override;
};

#endif //SETPOSITIONSYSTEM_H
