//
// Created by thoma on 24/03/2025.
//

#ifndef RENDERCUBESYSTEM_H
#define RENDERCUBESYSTEM_H
#include "component/BlockComponents.h"
#include "component/CameraComponents.h"
#include "System.h"
#include "component/BlockTextureComponent.h"
#include <ngl/Transformation.h>

#include "component/TransformComponents.h"

class RenderCubeSystem : public a_System<BlockTextureComponent>
{
public:
    ngl::Vec3 i_pos;
    CameraComponents* i_camera;
    TransformComponents* i_cameraTransform = nullptr;
    void run(BlockTextureComponent* io_component, int i_index) override;

};

#endif //RENDERCUBESYSTEM_H


