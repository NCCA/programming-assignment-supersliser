//
// Created by s5605187 on 22/03/25.
//

#ifndef COLONYMANAGER_MOVESYSTEM_H
#define COLONYMANAGER_MOVESYSTEM_H

#include "System.h"
#include "TransformComponent.h"


class MoveSystem : public a_System<TransformComponent> {
public:
    void run(TransformComponent& i_component) override;
};

#endif //COLONYMANAGER_MOVESYSTEM_H
