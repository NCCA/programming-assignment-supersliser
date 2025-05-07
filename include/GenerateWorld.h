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

/// @brief Generates a world using Perlin noise.
/// @param i_world Pointer to the world table.
/// @param i_xsize Size of the world in the x direction.
/// @param i_ysize Size of the world in the y direction.
/// @param i_zsize Size of the world in the z direction.
/// @param i_seed Seed for the Perlin noise generator.
void generateWorld(Table* i_world, int i_xsize, int i_ysize, int i_zsize, siv::PerlinNoise::seed_type i_seed);
/// @brief Utility function to get the noise value at a specific point.
/// @param noise The Perlin noise object.
/// @param x The x coordinate.
/// @param y The y coordinate.
/// @param scale The scale of the noise.
/// @return The noise value at the specified point between 0 - 1.
float getNoise(siv::PerlinNoise noise, int x, int y, float scale);

void growTree(Table* i_world, int i_xPos, int i_zPos, int i_yPos, int* i_blockCount);

void generateChunkedWorld(std::vector<Table>* i_world, Table* i_chunks, int i_xChunkSize, int i_zChunkSize, siv::PerlinNoise::seed_type i_seed);

#endif //COLONYMANAGERBUILD_GENERATEWORLD_H
