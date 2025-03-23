//
// Created by thoma on 22/03/2025.
//

#ifndef SETPOSITIONSYSTEM_H
#define SETPOSITIONSYSTEM_H

#include "System.h"
#include "Table.h"
#include "component/TransformComponent.h"

class SetPositionSystem : public a_System<TransformComponent>
{
public:
    ngl::Vec3 i_pos;
    void run(TransformComponent* io_component, int i_index) override;
};

#endif //SETPOSITIONSYSTEM_H
