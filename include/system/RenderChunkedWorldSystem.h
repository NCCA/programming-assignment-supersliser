//
// Created by s5605187 on 07/05/25.
//

#include "component/CameraComponents.h"
#include "System.h"
#include "Table.h"

#ifndef COLONYMANAGERBUILD_RENDERCHUNKEDWORLDSYSTEM_H
#define COLONYMANAGERBUILD_RENDERCHUNKEDWORLDSYSTEM_H

#endif //COLONYMANAGERBUILD_RENDERCHUNKEDWORLDSYSTEM_H

class RenderChunkedWorldSystem : public a_System<CameraComponents>
{
public:
    std::vector<Table> * i_chunkedWorld;
    void run(CameraComponents *io_component, int i_index) override;
};