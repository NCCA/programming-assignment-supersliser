//
// Created by s5605187 on 07/05/25.
//

#include "component/ChunkComponent.h"

ChunkComponent::ChunkComponent(size_t i_size)
{
    for (size_t i = 0; i < i_size; ++i)
    {
        m_loaded.emplace_back(false);
    }
}