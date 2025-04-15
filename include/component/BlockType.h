//
// Created by thoma on 29/03/2025.
//

#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

/// @class BlockType include/component/BlockType.h
/// @brief Enum class to define the different types of blocks
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-29
/// @details This enum class is used to define the different types of blocks in the game.\n The values are used to index into the texture atlas to get the correct texture for each block type.\n
enum Class BlockType
{
    None = 0,
    Grass = 1,
    Dirt = 2,
    Stone = 3,
    Log = 4,
    Leaves = 5,
    Planks = 6,
    };

#endif //BLOCKTYPE_H
