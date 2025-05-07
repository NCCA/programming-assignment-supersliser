//
// Created by s5605187 on 07/05/25.
//

#ifndef COLONYMANAGERBUILD_TESTCHUNKSYSTEM_H
#define COLONYMANAGERBUILD_TESTCHUNKSYSTEM_H

#include "component/ChunkComponent.h"
#include "System.h"

class TestChunkSystem : public a_System<ChunkComponent>
{
public:
    static int renderDistance() { return 4; }
    ngl::Vec3 i_playerPos;
    void run(ChunkComponent* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_TESTCHUNKSYSTEM_H
