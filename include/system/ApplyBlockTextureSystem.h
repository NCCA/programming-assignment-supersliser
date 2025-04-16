//
// Created by s5605187 on 26/03/25.
//

#ifndef COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H
#define COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H

#include <ngl/VAOFactory.h>
#include <ngl/MultiBufferVAO.h>

#include "system/System.h"
#include "component/BlockType.h"
#include "component/BlockTextureComponent.h"

/// @class ApplyBlockTextureSystem include/system/ApplyBlockTextureSystem.h
/// @brief System to apply textures to blocks
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-26
/// @details This system applies textures to blocks based on their type. It uses the BlockTextureComponent to store the texture information.
class ApplyBlockTextureSystem : public a_System<BlockTextureComponent>
{
public:
    /// @brief Static function to get the texture path based on the block type
    /// @param[in] i_blockType The block type
    /// @return string of path to block texture
    static std::string getTextureName(BlockType i_blockType)
    {
        switch (i_blockType)
        {
            case BlockType::None:
            default:
            return "textures/crate.bmp";
            case BlockType::Grass:
                return "textures/GrassTexture.bmp";
            case BlockType::Dirt:
                return "textures/DirtTexture.bmp";
            case BlockType::Stone:
            return "textures/StoneTexture.bmp";
            case BlockType::Log:
            return "textures/LogTexture.bmp";
            case BlockType::Leaves:
            return "textures/LeavesTexture.bmp";
            case BlockType::Planks:
            return "textures/PlanksTexture.bmp";
        }
    }
    /// @brief The BlockType to be applied when the system is run
    BlockType i_blockType;
    /// @brief Runs the system
    /// @param[in] io_component A pointer to the BlockTextureComponent to have the texture applied to it
    /// @param[in] i_index The index of the entity in the parent table
    /// @param[in] i_blockType [Required] The block type to be applied
    void run(BlockTextureComponent* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H
