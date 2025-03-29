//
// Created by thoma on 24/03/2025.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include <ngl/Mat4.h>
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include "Camera.h"
class CameraComponents
{
    public:
    explicit CameraComponents(size_t i_size);
    std::vector<Camera> m_cameras;
    static std::uint8_t getComponentID() { return 4; }
};

#endif //CAMERACOMPONENT_H
