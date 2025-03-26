//
// Created by thoma on 24/03/2025.
//

#ifndef RENDERWORLDSYSTEM_H
#define RENDERWORLDSYSTEM_H
#include "component/BlockComponents.h"
#include "component/CameraComponents.h"

#endif //RENDERWORLDSYSTEM_H

#include "System.h"
#include "component/BlockTextureComponent.h"

class RenderCubeSystem : public a_System<BlockComponents>
{
    public:
    ngl::Vec3 i_pos;
    CameraComponents* m_camera;
    BlockTextureComponent* m_texture;
    void run(BlockComponents* io_component, int i_index) override;

};