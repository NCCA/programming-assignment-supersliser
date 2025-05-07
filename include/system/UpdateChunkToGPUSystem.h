//
// Created by s5605187 on 07/05/25.
//

#ifndef COLONYMANAGERBUILD_UPDATECHUNKTOGPUSYSTEM_H
#define COLONYMANAGERBUILD_UPDATECHUNKTOGPUSYSTEM_H

#include <ngl/Vec3.h>
#include "component/ChunkComponent.h"
#include "System.h"
#include "Table.h"

class UpdateChunkToGPUSystem : public a_System<ChunkComponent>
{
public:
    std::vector<Table>* i_world = nullptr;
    void run(ChunkComponent* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_UPDATECHUNKTOGPUSYSTEM_H
