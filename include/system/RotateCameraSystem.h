//
// Created by thoma on 30/03/2025.
//

#ifndef ROTATECAMERASYSTEM_H
#define ROTATECAMERASYSTEM_H

#include <component/CameraComponents.h>
#include "system/System.h"

class RotateCameraSystem : public a_System<CameraComponents>
{
    public:
    ngl::Vec2 i_mouseDelta;
    float s_sensitivity = 0.1f;
    void run(CameraComponents* io_component, int i_index) override;
};

#endif //ROTATECAMERASYSTEM_H
