//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_MOVESYSTEM_H
#define COLONYMANAGER_MOVESYSTEM_H

#include "System.h"
#include "Table.h"
#include "component/TransformComponents.h"


class MoveSystem : public a_System<TransformComponents> {
public:
    Table* i_world = nullptr;
    ngl::Vec3 i_pos;
    void run(TransformComponents* io_component, int i_index) override;
};

#endif //COLONYMANAGER_MOVESYSTEM_H
