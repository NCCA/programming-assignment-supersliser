//
// Created by s5605187 on 06/04/25.
//

#include "GenerateWorld.h"
#include "component/ChunkComponent.h"

void generateWorld(Table* i_world, int i_xsize, int i_ysize, int i_zsize, siv::PerlinNoise::seed_type i_seed)
{
    float scale = 0.025f;
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
            }
        }
    }

    for (int i = 0; i < (i_xsize + i_zsize) / 2; i++)
    {
        int xPos = random() % i_xsize;
        int zPos = random() % i_zsize;
        int yPos = (int)(i_ysize * getNoise(noise, xPos, zPos, scale));
        growTree(i_world, xPos, zPos, yPos, &blockCount);
    }
}

void generateChunkedWorld(std::vector<Table>* i_world, Table* i_chunks, int i_xChunkSize, int i_zChunkSize, siv::PerlinNoise::seed_type i_seed) {
    float scale = 0.025f;
    siv::PerlinNoise noise{i_seed};
    int blockCount = 0;
    int chunkCount = 0;

    for (int x = 0; x < i_xChunkSize; x++) {
        for (int z = 0; z < i_zChunkSize; z++) {
                i_chunks->createEntity();
                i_world->push_back(Table());
                i_world->back().createEntity();

                chunkCount++;
                for (int x = 0; x < ChunkComponent::chunkSize(); x++) {
                    for (int z = 0; z < ChunkComponent::chunkSize(); z++) {
                        for (int y = 0; y < ChunkComponent::chunkSize() * getNoise(noise, x, z, scale) + 5; y++) {
                            i_world->back().createEntity();
                            blockCount++;
                        }
                    }
                }
                i_world->back().registerComponentType(BlockComponents::getComponentID());
                i_world->back().registerComponentType(BlockTextureComponent::getComponentID());
                i_world->back().registerComponentType(TransformComponents::getComponentID());
                i_world->back().registerComponentType(ChunkComponent::getComponentID());
            }
        }

    i_chunks->registerComponentType(ChunkComponent::getComponentID());
    i_chunks->registerComponentType(TransformComponents::getComponentID());

    SetPositionSystem setPositionSystem;

    //in this system, x is left - right, y is up - down, z is forward - back
    chunkCount = 0;
    for (int x = 0; x < i_xChunkSize; x++)
    {
        for (int z = 0; z < i_zChunkSize; z++)
        {
            setPositionSystem.i_pos = ngl::Vec3(x * ChunkComponent::chunkSize(), 0, z * ChunkComponent::chunkSize());
            i_chunks->run(&setPositionSystem, TransformComponents::getComponentID(), chunkCount, chunkCount);
            chunkCount++;
        }
    }

    blockCount = 0;
    chunkCount = 0;

    for (int cx = 0; cx < i_xChunkSize; cx++)
    {
        for (int cz = 0; cz < i_zChunkSize; cz++)
        {
            for (int x = 0; x < ChunkComponent::chunkSize(); x++)
            {
                for (int z = 0; z < ChunkComponent::chunkSize(); z++)
                {
            for (int y = -5; y < ChunkComponent::chunkSize() * getNoise(noise, x, z, scale); y++)
            {
                if (y < ChunkComponent::chunkSize() * getNoise(noise, x, z, scale) - 7)
                {
                    ApplyBlockTextureSystem applyBlockTextureSystem;
                    applyBlockTextureSystem.i_blockType = BlockType::Stone;
                    i_world->at(chunkCount).run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), blockCount,
                                 blockCount);
                }
                else if (y < ChunkComponent::chunkSize() * getNoise(noise, x, z, scale) - 3)
                {
                    ApplyBlockTextureSystem applyBlockTextureSystem;
                    applyBlockTextureSystem.i_blockType = BlockType::Dirt;
                    i_world->at(chunkCount).run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), blockCount,
                                 blockCount);
                }
                else
                {
                    ApplyBlockTextureSystem applyBlockTextureSystem;
                    applyBlockTextureSystem.i_blockType = BlockType::Grass;
                    i_world->at(chunkCount).run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), blockCount,
                                 blockCount);
                }
                setPositionSystem.i_pos = ngl::Vec3(x % ChunkComponent::chunkSize(), y % ChunkComponent::chunkSize(), z % ChunkComponent::chunkSize());
                i_world->at(chunkCount).run(&setPositionSystem, TransformComponents::getComponentID(), blockCount, blockCount);
                blockCount++;
            }
                }
            }
            chunkCount++;
        }
    }
}
float getNoise(siv::PerlinNoise noise, int x, int y, float scale)
{
    return std::clamp((float)noise.noise2D(x * scale, y * scale) * 0.5f + 0.5f, 0.2f, 1.0f);
}

void growTree(Table* i_world, int i_xPos, int i_zPos, int i_yPos, int* i_blockCount)
{
    for (int i = 0; i < 5; i++)
    {
        i_world->createEntity();
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Log;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), *i_blockCount, *i_blockCount);
        SetPositionSystem setPositionSystem;
        setPositionSystem.i_pos = ngl::Vec3(i_xPos, i_yPos + i, i_zPos);
        i_world->run(&setPositionSystem, TransformComponents::getComponentID(), *i_blockCount, *i_blockCount);
        (*i_blockCount)++;
    }

    for (int y = 3; y < 7; y++) {
        for (int x = -2; x < 3; x++) {
            for (int z = -2; z < 3; z++) {
                i_world->createEntity();
                ApplyBlockTextureSystem applyBlockTextureSystem;
                applyBlockTextureSystem.i_blockType = BlockType::Leaves;
                i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), *i_blockCount, *i_blockCount);
                SetPositionSystem setPositionSystem;
                setPositionSystem.i_pos = ngl::Vec3(i_xPos + x, y + i_yPos, i_zPos + z);
                i_world->run(&setPositionSystem, TransformComponents::getComponentID(), *i_blockCount, *i_blockCount);
                (*i_blockCount)++;
            }
        }
    }
}