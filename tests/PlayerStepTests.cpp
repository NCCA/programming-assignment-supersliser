//
// Created by thoma on 31/03/2025.
//


#include <SDL2/SDL.h>
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>

#include "Table.h"
#include "Utils.h"
#include "component/BlockComponents.h"
#include "component/BlockTextureComponent.h"
#include "component/CameraComponents.h"
#include "system/ApplyBlockTextureSystem.h"
#include "system/MovePlayerSystem.h"
#include "system/PlayerFallSystem.h"
#include "system/RenderWorldSystem.h"
#include "system/RotateCameraSystem.h"
#include "system/SetPositionSystem.h"
#include "SDLWindowManager.h"

TEST(PlayerStep, PlayerStepUp) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, true, false, false, true, 0);
    windowManager.createWindow("Step Up TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 6; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float j = 0; j < 4; j++) {
            ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
            i_world->run(&ms, TransformComponents::getComponentID(), j, j);
        }
        for (float j = 4; j < 6; j++) {
            ms.i_pos = ngl::Vec3(0.0f, 1.0f, (j - 1));
            i_world->run(&ms, TransformComponents::getComponentID(), j, j);
        }

        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can step up if blocked");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(PlayerStep, PlayerWall) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, true, false, false, true, 0);
    windowManager.createWindow("Step Wall TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 6; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float j = 0; j < 4; j++) {
            ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
            i_world->run(&ms, TransformComponents::getComponentID(), j, j);
        }
        for (float j = 1; j < 3; j++) {
            ms.i_pos = ngl::Vec3(0.0f, j, 3.0f);
            i_world->run(&ms, TransformComponents::getComponentID(), j + 3, j + 3);
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player will be blocked");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(PlayerStep, PlayerTopBlockWall) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, true, false, false, true, 0);
    windowManager.createWindow("Blocked by Top of Wall TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 6; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float j = 0; j < 4; j++) {
            ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
            i_world->run(&ms, TransformComponents::getComponentID(), j, j);
        }
        for (float j = 1; j < 3; j++) {
            ms.i_pos = ngl::Vec3(0.0f, j + 1, 3.0f);
            i_world->run(&ms, TransformComponents::getComponentID(), j + 3, j + 3);
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player will be blocked by top of wall only");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(PlayerStep, PlayerBlockedAbove) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, true, false, false, true, 0);
    windowManager.createWindow("Blocked from Above TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 6; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float j = 0; j < 4; j++) {
            ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
            i_world->run(&ms, TransformComponents::getComponentID(), j, j);
        }
        ms.i_pos = ngl::Vec3(0.0f, 1, 3.0f);
        i_world->run(&ms, TransformComponents::getComponentID(), 4, 4);
        ms.i_pos = ngl::Vec3(0.0f, 3, 2.0f);
        i_world->run(&ms, TransformComponents::getComponentID(), 5, 5);
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player will be blocked from above and by step");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(PlayerStep, PlayerStepDown) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, true, false, false, true, 1);
    windowManager.createWindow("Step Down TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 6; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float j = 0; j < 4; j++) {
            ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
            i_world->run(&ms, TransformComponents::getComponentID(), j, j);
        }
        ms.i_pos = ngl::Vec3(0.0f, -1.0f, 3.0f);
        i_world->run(&ms, TransformComponents::getComponentID(), 4, 4);
        ms.i_pos = ngl::Vec3(0.0f, -1.0f, 4.0f);
        i_world->run(&ms, TransformComponents::getComponentID(), 5, 5);
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player will step down");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(PlayerStep, PlayerFallTest) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, true, false, false, true, 1);
    windowManager.createWindow("Step Fall TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 29; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float j = 0; j < 4; j++) {
            ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
            i_world->run(&ms, TransformComponents::getComponentID(), j, j);
        }
        for (float x = -2.0f; x < 3.0f; x++) {
            for (float z = -2.0f; z < 3.0f; z++) {
                ms.i_pos = ngl::Vec3(x, -50.0f, z + 5);
                i_world->run(&ms, TransformComponents::getComponentID(), (x + 2) * 5 + (z + 2) + 4, (x + 2) * 5 + (z + 2) + 4);
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player will fall down");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}
