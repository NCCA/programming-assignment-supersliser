//
// Created by t on 07/05/25.
//

#ifndef CHUNKCOMPONENT_H
#define CHUNKCOMPONENT_H

#include <cstdio>
#include <ngl/Vec3.h>

class ChunkComponent {
 public:
    ChunkComponent(size_t i_size);
    static int chunkSize() { return 8; }
    std::vector<bool> m_loaded;
    static std::uint8_t getComponentID() { return 9; }
};

#endif //CHUNKCOMPONENT_H
