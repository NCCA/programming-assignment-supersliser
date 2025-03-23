//
// Created by thoma on 23/03/2025.
//

#ifndef TESTISBLOCKEDSYSTEM_H
#define TESTISBLOCKEDSYSTEM_H
#include "System.h"
#include "component/PositionComponent.h"

class TestIsBlockedSystem : public a_System<PositonComponent>
{
public:
    void run(PositonComponent* io_component, int i_index, void* i_world, std::vector<float> i_args) override;
    bool o_output = false;
};

#endif //TESTISBLOCKEDSYSTEM_H
