//
// Created by thoma on 23/03/2025.
//

#include "component/BlockComponents.h"

BlockComponents::BlockComponents(size_t i_size)
{
    for (int i = 0; i < i_size; i++) {
        m_parentChunk.push_back(0);
    }
}
