//
// Created by thoma on 23/03/2025.
//
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>
#include <SDL2/SDL.h>

#include "Table.h"
#include "component/BlockComponents.h"
#include "component/CameraComponents.h"
#include "system/RenderWorldSystem.h"
#include "system/SetPositionSystem.h"
#include "system/ApplyBlockTextureSystem.h"
#include "Utils.h"
#include "system/SetCameraLookSystem.h"
#include "SDLWindowManager.h"

/// @brief Tests if the world can be displayed in an SDL window.
/// @result A single grass block floating in a grey background. The block will appear slightly to the left of the screen and diagonally rotated to the camera.
TEST(WorldDisplay, WorldVisible) {
    SDLWindowManager windowManager = SDLWindowManager(0, 1, 0, 0, 0, 0, 0, 0, 0);
    windowManager.createWindow("World Visible TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 1; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        ms.i_pos = ngl::Vec3(0.0f, 0.0f, 1.0f);
        i_world->run(&ms, TransformComponents::getComponentID());
        SetCameraLookSystem setCameraLookSystem;
        setCameraLookSystem.i_pos = ngl::Vec3(2.0f, 2.0f, 2.0f);
        setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
        i_players->run(&setCameraLookSystem, CameraComponents::getComponentID());

        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("single block is visible");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

/// @brief Tests if multiple blocks can be displayed in an SDL window
/// @result a 3x3 of grass blocks directly above a 3x3 of brown dirt blocks. The blocks will appear central in the screen and diagonally rotated to the camera.
TEST(WorldDisplay, WorldMultiBlockVisible) {
    SDLWindowManager windowManager = SDLWindowManager(0, 1, 0, 0, 0, 0, 0, 0, 0);
    windowManager.createWindow("MutliBlock Visible TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 9; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -1; i <= 1; i++) {
            for (float j = -1; j <= 1; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i * 1, 0.0f, j * 1);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 1) * 3 + (j + 1), (i + 1) * 3 + (j + 1));
            }
        }

        SetCameraLookSystem setCameraLookSystem;
        setCameraLookSystem.i_pos = ngl::Vec3(4.0f, 4.0f, 4.0f);
        setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
        i_players->run(&setCameraLookSystem, CameraComponents::getComponentID());

        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());
        for (float i = -1; i <= 1; i++) {
            for (float j = -1; j <= 1; j++) {
                i_world->createEntity();
                ms.i_pos = ngl::Vec3(i * 1, -1.0f, j * 1);
                i_world->run(&ms, TransformComponents::getComponentID(), 9 + (i + 1) * 3 + (j + 1), 9 + (i + 1) * 3 + (j + 1));
            }
        }
        applyBlockTextureSystem.i_blockType = BlockType::Dirt;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), 9, 18);

        utils::printTestString("multiple blocks are visible");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

/// @brief Tests all textures and makes sure that they display properly.
/// @result All possible blocks (see include/component/BlockType.h for a list of all possible blocks).
/// @note The null block should be displayed as a crate.
TEST(WorldDisplay, AllTextureTest) {
    SDLWindowManager windowManager = SDLWindowManager(0, 1, 0, 0, 0, 0, 0, 0, 0);
    windowManager.createWindow("All Texture TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        constexpr int TEXTURE_COUNT = 7;
        for (uint32_t i = 0; i < TEXTURE_COUNT; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;

        SetCameraLookSystem setCameraLookSystem;
        setCameraLookSystem.i_pos = ngl::Vec3(4.0f, 4.0f, 4.0f);
        setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
        i_players->run(&setCameraLookSystem, CameraComponents::getComponentID());

        ApplyBlockTextureSystem applyBlockTextureSystem;
        for (int i = 0; i < TEXTURE_COUNT; i++) {
            ms.i_pos = ngl::Vec3(i - TEXTURE_COUNT / 2, 0.0f, 0.0f);
            i_world->run(&ms, TransformComponents::getComponentID(), i, i);
            applyBlockTextureSystem.i_blockType = static_cast<BlockType>(i);
            i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), i, i);
        }

        utils::printTestString("multiple blocks are visible");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}
