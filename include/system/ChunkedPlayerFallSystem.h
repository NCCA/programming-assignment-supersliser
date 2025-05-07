//
// Created by s5605187 on 07/05/25.
//

#ifndef COLONYMANAGERBUILD_CHUNKEDPLAYERFALLSYSTEM_H
#define COLONYMANAGERBUILD_CHUNKEDPLAYERFALLSYSTEM_H

#include "component/CameraComponents.h"
#include "System.h"
#include "component/SpeedComponent.h"
#include "Table.h"

class ChunkedPlayerFallSystem : public a_System<CameraComponents>
{
public:
    SpeedComponent* i_speed = nullptr;
    std::vector<Table>* i_chunkedWorld = nullptr;
    void run(CameraComponents* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_CHUNKEDPLAYERFALLSYSTEM_H
