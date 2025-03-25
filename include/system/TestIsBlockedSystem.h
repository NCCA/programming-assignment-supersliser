//
// Created by thoma on 23/03/2025.
//

#ifndef TESTISBLOCKEDSYSTEM_H
#define TESTISBLOCKEDSYSTEM_H
#include "System.h"
#include "Table.h"
#include "component/TransformComponents.h"

class TestIsBlockedSystem : public a_System<TransformComponents>
{
public:
    Table* i_world = nullptr;
    ngl::Vec3 i_pos;
    void run(TransformComponents* io_component, int i_index) override;
    bool o_output = false;
};

#endif //TESTISBLOCKEDSYSTEM_H
