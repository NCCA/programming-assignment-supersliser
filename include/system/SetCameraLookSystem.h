//
// Created by s5605187 on 29/03/25.
//

#ifndef COLONYMANAGERBUILD_SETCAMERALOOKSYSTEM_H
#define COLONYMANAGERBUILD_SETCAMERALOOKSYSTEM_H

#include "component/CameraComponents.h"
#include "System.h"

class SetCameraLookSystem : public a_System<CameraComponents>
{
public:
    void run(CameraComponents* io_component, int i_index) override;
    ngl::Vec3 i_pos;
    ngl::Vec3 i_look;
};

#endif //COLONYMANAGERBUILD_SETCAMERALOOKSYSTEM_H
