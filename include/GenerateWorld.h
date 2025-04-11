//
// Created by s5605187 on 06/04/25.
//

#ifndef COLONYMANAGERBUILD_GENERATEWORLD_H
#define COLONYMANAGERBUILD_GENERATEWORLD_H

#include "Table.h"
#include "component/TransformComponents.h"
#include "component/BlockComponents.h"
#include "component/BlockTextureComponent.h"
#include "component/IsSprintingComponent.h"
#include "component/SpeedComponent.h"
#include "component/CameraComponents.h"
#include "PerlinNoise.hpp"
#include "component/BlockType.h"
#include "system/SetPositionSystem.h"
#include "system/ApplyBlockTextureSystem.h"

void generateWorld(Table* i_world, int i_xsize, int i_ysize, int i_zsize, siv::PerlinNoise::seed_type i_seed);
float getNoise(siv::PerlinNoise noise, int x, int y, float scale);

#endif //COLONYMANAGERBUILD_GENERATEWORLD_H
