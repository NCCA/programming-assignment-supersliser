//
// Created by t on 07/05/25.
//

#ifndef CHUNKCOMPONENT_H
#define CHUNKCOMPONENT_H

class ChunkComponent {
 public:
    ChunkComponent(size_t i_size);
    std::vector<ngl::Vec3> m_pos;
    static std::uint8_t getComponentID() { return 9; }
};

#endif //CHUNKCOMPONENT_H
