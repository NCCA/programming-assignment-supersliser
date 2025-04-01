//
// Created by thoma on 01/04/2025.
//

#ifndef PLAYERFALLSYSTEM_H
#define PLAYERFALLSYSTEM_H

#include "component/SpeedComponent.h"
#include "component/CameraComponents.h"
#include "system/System.h"
#include "Table.h"
#include "system/TestIsBlockedSystem.h"

class PlayerFallSystem : a_System<CameraComponents>
{
    public:
    SpeedComponent* i_speed = nullptr;
    Table* i_world = nullptr;
    void run(CameraComponents* io_component, int i_index) override;
};

#endif //PLAYERFALLSYSTEM_H
