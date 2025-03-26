//
// Created by s5605187 on 26/03/25.
//

#include "system/ApplyBlockTextureSystem.h"

void ApplyBlockTextureSystem::run(BlockTextureComponent* io_component, int i_index)
{
    ngl::Texture t;
    t.loadImage("/home/s5605187/Documents/programming-assignment-supersliser/textures/crate.bmp");
    io_component->m_textures[i_index] = t.setTextureGL();
}