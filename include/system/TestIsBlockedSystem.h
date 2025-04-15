//
// Created by thoma on 23/03/2025.
//

#ifndef TESTISBLOCKEDSYSTEM_H
#define TESTISBLOCKEDSYSTEM_H
#include "System.h"
#include "Table.h"
#include "component/TransformComponents.h"

/// @class TestIsBlockedSystem include/system/TestIsBlockedSystem.h
/// @brief System to test if a block is at a position
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-23
/// @details This system tests if a block is at a position. It uses the TransformComponents to access the position information.
class TestIsBlockedSystem : public a_System<TransformComponents>
{
public:
  /// @brief Pointer to the table of blocks
    Table* i_world = nullptr;
    /// @brief The position to test
    ngl::Vec3 i_pos;
    /// @brief run the system
    /// @param[in] io_component A pointer to the TransformComponents to have the position tested
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_world [Required] The table of blocks to test against
    /// @param[in] i_pos [Required] The position to test
    /// @return True if there is a block at the position, false otherwise
    void run(TransformComponents* io_component, int i_index) override;
    /// @brief The result of the test
    /// @note True if there is a block at the position, false otherwise
    bool o_output = false;
};

#endif //TESTISBLOCKEDSYSTEM_H
