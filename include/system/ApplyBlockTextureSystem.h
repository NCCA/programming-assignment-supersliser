//
// Created by s5605187 on 26/03/25.
//

#ifndef COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H
#define COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H

#include "System.h"
#include "component/BlockTextureComponent.h"
#include <ngl/VAOFactory.h>
#include <ngl/MultiBufferVAO.h>
class ApplyBlockTextureSystem : public a_System<BlockTextureComponent>
{
public:
    std::string_view i_texturePath = "/home/tom/programming-assignment-supersliser/textures/crate.bmp";
    void run(BlockTextureComponent* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_APPLYBLOCKTEXTURESYSTEM_H
