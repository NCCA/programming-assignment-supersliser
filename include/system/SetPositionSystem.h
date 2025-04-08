//
// Created by thoma on 22/03/2025.
//

#ifndef SETPOSITIONSYSTEM_H
#define SETPOSITIONSYSTEM_H

#include "System.h"
#include "Table.h"
#include "component/TransformComponents.h"
#include <ngl/ShaderLib.h>
#include <ngl/AbstractVAO.h>
#include <ngl/MultiBufferVAO.h>

#include "nglExtension/MultiBufferInstanceVAO.h"


class SetPositionSystem : public a_System<TransformComponents>
{
public:
    ngl::Vec3 i_pos;
    std::vector<std::shared_ptr<MultiBufferInstanceVAO>>* i_vaos;
    void run(TransformComponents* io_component, int i_index) override;
};

#endif //SETPOSITIONSYSTEM_H
