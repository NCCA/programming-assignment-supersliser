//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_MOVESYSTEM_H
#define COLONYMANAGER_MOVESYSTEM_H

#include "System.h"
#include "PositionComponent.h"


class MoveSystem : public a_System<PositonComponent> {
public:
    void run(PositonComponent& i_component, int i_index) override;
};

#endif //COLONYMANAGER_MOVESYSTEM_H
