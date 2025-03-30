//
// Created by thoma on 24/03/2025.
//

#ifndef RENDERWORLDSYSTEM_H
#define RENDERWORLDSYSTEM_H
#include "System.h"
#include "Table.h"
#include "component/CameraComponents.h"
#include "component/TransformComponents.h"

class RenderWorldSystem : public a_System<CameraComponents>
{
public:
    Table* i_world;
    void run(CameraComponents* io_component, int i_index) override;
};
#endif //RENDERWORLDSYSTEM_H
