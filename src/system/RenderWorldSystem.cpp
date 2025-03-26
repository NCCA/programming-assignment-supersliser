//
// Created by thoma on 24/03/2025.
//

#include "system/RenderWorldSystem.h"

#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include "component/BlockComponents.h"
#include "component/TransformComponents.h"
#include "system/RenderCubeSystem.h"

void RenderWorldSystem::run(CameraComponents* io_component, int i_index) {
    for (int i = 0; i < static_cast<TransformComponents*>(i_world->getColumn(i_world->getComponentIndex(TransformComponents::getComponentID())).get())->m_ps.size(); i++)
    {
        RenderCubeSystem renderCubeSystem;
        renderCubeSystem.i_pos = static_cast<TransformComponents*>(i_world->getColumn(i_world->getComponentIndex(TransformComponents::getComponentID())).get())->m_ps[i];
        renderCubeSystem.m_camera = i_cams;
        renderCubeSystem.m_texture = static_cast<BlockTextureComponent*>(i_world->getColumn(i_world->getComponentIndex(BlockTextureComponent::getComponentID())).get());
        renderCubeSystem.run(static_cast<BlockComponents*>(i_world->getColumn(i_world->getComponentIndex(BlockComponents::getComponentID())).get()), i);
    }
}
