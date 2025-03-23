//
// Created by thoma on 22/03/2025.
//

#ifndef SETPOSITIONSYSTEM_H
#define SETPOSITIONSYSTEM_H

#include "System.h"
#include "Table.h"
#include "component/PositionComponent.h"

class SetPositionSystem : public a_System<PositonComponent>
{
public:
    void run(PositonComponent* io_component, int i_index, void* i_world, std::vector<float> i_args) override;
};

#endif //SETPOSITIONSYSTEM_H
