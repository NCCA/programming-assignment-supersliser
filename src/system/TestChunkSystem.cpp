//
// Created by s5605187 on 07/05/25.
//


#include "system/TestChunkSystem.h"

void TestChunkSystem::run(ChunkComponent* io_component, int i_index)
{
    // Check if the chunk is within the render distance of the player
    ngl::Vec3 i_playerPos = i_playerPos;
    for (size_t i = 0; i < io_component->m_pos.size(); ++i)
    {
        if (io_component->m_pos[i].m_x > i_playerPos.m_x - renderDistance() * ChunkComponent::chunkSize() &&
            io_component->m_pos[i].m_x < i_playerPos.m_x + renderDistance() * ChunkComponent::chunkSize() &&
            io_component->m_pos[i].m_y > i_playerPos.m_y - renderDistance() * ChunkComponent::chunkSize() &&
            io_component->m_pos[i].m_y < i_playerPos.m_y + renderDistance() * ChunkComponent::chunkSize() &&
            io_component->m_pos[i].m_z > i_playerPos.m_z - renderDistance() * ChunkComponent::chunkSize() &&
            io_component->m_pos[i].m_z < i_playerPos.m_z + renderDistance() * ChunkComponent::chunkSize())
        {
            io_component->m_loaded[i] = true;
        }
        else
        {
            io_component->m_loaded[i] = false;
        }
    }
}