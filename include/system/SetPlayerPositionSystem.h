//
// Created by s5605187 on 06/04/25.
//

#ifndef COLONYMANAGERBUILD_SETPLAYERPOSITIONSYSTEM_H
#define COLONYMANAGERBUILD_SETPLAYERPOSITIONSYSTEM_H

#include "System.h"
#include "component/CameraComponents.h"

class SetPlayerPositionSystem : public a_System<CameraComponents>
{
public:
    ngl::Vec4 i_pos;
    void run(CameraComponents* io_component, int i_index) override;
};

#endif //COLONYMANAGERBUILD_SETPLAYERPOSITIONSYSTEM_H
