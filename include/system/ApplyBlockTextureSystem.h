//
// Created by s5605187 on 26/03/25.
//

#ifndef COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H
#define COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H

#include "System.h"
#include "component/BlockTextureComponent.h"
#include <ngl/VAOFactory.h>
#include <ngl/MultiBufferVAO.h>

#include "component/BlockType.h"

class ApplyBlockTextureSystem : public a_System<BlockTextureComponent>
{
public:
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
    BlockType i_blockType;
    void run(BlockTextureComponent* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H
