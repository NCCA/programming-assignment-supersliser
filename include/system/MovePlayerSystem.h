//
// Created by s5605187 on 30/03/25.
//

#ifndef COLONYMANAGERBUILD_MOVEPLAYERSYSTEM_H
#define COLONYMANAGERBUILD_MOVEPLAYERSYSTEM_H

#include "system/System.h"
#include "component/CameraComponents.h"
#include "Table.h"
#include "component/IsSprintingComponent.h"
#include "component/SpeedComponent.h"

class MovePlayerSystem : public a_System<CameraComponents>
{
public:
    ngl::Vec3 i_dir;
    Table* i_world = nullptr;
    IsSprintingComponent* i_isSprinting = nullptr;
    SpeedComponent* i_speed = nullptr;

    void run(CameraComponents* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_MOVEPLAYERSYSTEM_H
