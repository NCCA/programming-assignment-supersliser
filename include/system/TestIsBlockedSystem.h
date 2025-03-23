//
// Created by thoma on 23/03/2025.
//

#ifndef TESTISBLOCKEDSYSTEM_H
#define TESTISBLOCKEDSYSTEM_H
#include "System.h"
#include "Table.h"
#include "component/TransformComponent.h"

class TestIsBlockedSystem : public a_System<TransformComponent>
{
public:
    Table* i_world = nullptr;
    ngl::Vec3 i_pos;
    void run(TransformComponent* io_component, int i_index) override;
    bool o_output = false;
};

#endif //TESTISBLOCKEDSYSTEM_H
