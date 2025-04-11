//
// Created by s5605187 on 06/04/25.
//

#include "GenerateWorld.h"

void generateWorld(Table* i_world, int i_xsize, int i_ysize, int i_zsize, siv::PerlinNoise::seed_type i_seed)
{
    float scale = i_xsize / 1000.0f;
    siv::PerlinNoise noise{i_seed};
    int blockCount = 0;
    for (int x = 0; x < i_xsize; x++)
    {
        for (int z = 0; z < i_zsize; z++)
        {
            for (int y = 0; y < i_ysize * getNoise(noise, x, z, scale) + 5; y++)
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
            for (int y = -5; y < i_ysize * getNoise(noise, x, z, scale); y++)
            {
                if (y < i_ysize * getNoise(noise, x, z, scale) - 7)
                {
                    ApplyBlockTextureSystem applyBlockTextureSystem;
                    applyBlockTextureSystem.i_blockType = BlockType::Stone;
                    i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), blockCount,
                                 blockCount);
                }
                else if (y < i_ysize * getNoise(noise, x, z, scale) - 3)
                {
                    ApplyBlockTextureSystem applyBlockTextureSystem;
                    applyBlockTextureSystem.i_blockType = BlockType::Dirt;
                    i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), blockCount,
                                 blockCount);
                }
                else
                {
                    ApplyBlockTextureSystem applyBlockTextureSystem;
                    applyBlockTextureSystem.i_blockType = BlockType::Grass;
                    i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), blockCount,
                                 blockCount);
                }
                setPositionSystem.i_pos = ngl::Vec3(x, y, z);
                i_world->run(&setPositionSystem, TransformComponents::getComponentID(), blockCount, blockCount);
                blockCount++;
                printf("Block %d: %d %d %d\n", blockCount, x, y, z);
            }
        }
    }
}

float getNoise(siv::PerlinNoise noise, int x, int y, float scale)
{
    return std::clamp((float)noise.noise2D(x * scale, y * scale) * 0.5f + 0.5f, 0.75f, 1.0f);
}
