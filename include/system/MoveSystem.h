//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_MOVESYSTEM_H
#define COLONYMANAGER_MOVESYSTEM_H

#include "System.h"
#include "Table.h"
#include "component/TransformComponent.h"


class MoveSystem : public a_System<TransformComponent> {
public:
    Table* i_world = nullptr;
    ngl::Vec3 i_pos;
    void run(TransformComponent* io_component, int i_index) override;
};

#endif //COLONYMANAGER_MOVESYSTEM_H
