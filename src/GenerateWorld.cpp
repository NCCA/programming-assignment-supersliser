//
// Created by s5605187 on 06/04/25.
//

#include "GenerateWorld.h"

void generateWorld(Table* i_world, int i_xsize, int i_ysize, int i_zsize, siv::PerlinNoise::seed_type i_seed)
{
    siv::PerlinNoise noise {i_seed};
    int blockCount = 0;
    for (int x = 0; x < i_xsize; x++)
    {
        for (int z = 0; z < i_zsize; z++)
        {
            for (int y = 0; y < i_ysize * getNoise(noise, x, z) + 5; y++)
            {
                i_world->createEntity();
                blockCount++;
            }
        }
    }
    i_world->registerComponentType(BlockComponents::getComponentID());
    i_world->registerComponentType(BlockTextureComponent::getComponentID());
    i_world->registerComponentType(TransformComponents::getComponentID());

    SetPositionSystem setPositionSystem;

    //in this system, x is left - right, y is up - down, z is forward - back

    blockCount = 0;
    for (int x = 0; x < i_xsize; x++)
    {
        for (int z = 0; z < i_zsize; z++)
        {
            for (int y = 0; y < i_ysize * getNoise(noise, x, z) + 5; y++)
            {
//                if (y - 5 < i_ysize * noise.noise2D(x, z) - 1) {
//                    ApplyBlockTextureSystem applyBlockTextureSystem;
//                    applyBlockTextureSystem.i_blockType = BlockType::Grass;
//                    i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), x * i_ysize * i_zsize + z * i_zsize + y, x * i_ysize * i_zsize + z * i_zsize + y);
//                }
//                else if (y - 6 < i_ysize * noise.noise2D(x, z) - 4) {
//                    ApplyBlockTextureSystem applyBlockTextureSystem;
//                    applyBlockTextureSystem.i_blockType = BlockType::Dirt;
//                    i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), x * i_ysize * i_zsize + z * i_zsize + y, x * i_ysize * i_zsize + z * i_zsize + y);
//                }
//                else {
                    ApplyBlockTextureSystem applyBlockTextureSystem;
                    applyBlockTextureSystem.i_blockType = BlockType::Stone;
                    i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), blockCount, blockCount);
//                }
                setPositionSystem.i_pos = ngl::Vec3(x, y - 5, z);
                i_world->run(&setPositionSystem, TransformComponents::getComponentID(), blockCount, blockCount);
blockCount++;
            }
        }
    }
}

float getNoise(siv::PerlinNoise noise, int x, int y)
{
    return std::clamp((float)noise.noise2D(x, y) + 5, 0.5f, 1.0f);
}