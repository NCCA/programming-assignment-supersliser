//
// Created by thoma on 24/03/2025.
//

#ifndef RENDERWORLDSYSTEM_H
#define RENDERWORLDSYSTEM_H
#include "System.h"
#include "Table.h"
#include "component/CameraComponents.h"

class RenderWorldSystem : public a_System<CameraComponents>
{
public:
    Table* i_world;
    CameraComponents* i_cams;
    void run(CameraComponents* io_component, int i_index) override;
};
#endif //RENDERWORLDSYSTEM_H
