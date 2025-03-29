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

    static std::string getTextureDir()
    {
#ifdef __amd64__
        return "/home/tom/programming-assignment-supersliser/textures/";
#elif __linux__
        return "/home/s5605187/Documents/programming-assignment-supersliser/textures/";
#endif
    }

    static std::string getTextureName(BlockType i_blockType)
    {
        switch (i_blockType)
        {
            case BlockType::Grass:
                return "GrassTexture.bmp";
            case BlockType::Dirt:
                return "DirtTexture.bmp";
            default:
                return "crate.bmp";
        }
    }
    BlockType i_blockType;
    void run(BlockTextureComponent* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H
