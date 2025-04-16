//
// Created by thoma on 29/03/2025.
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
#include "system/RenderWorldSystem.h"
#include "system/RotateCameraSystem.h"
#include "system/SetSprintingSystem.h"
#include "system/SetPositionSystem.h"
#include "SDLWindowManager.h"

TEST(Player, PlayerMoveForwards) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, 0, 0, 0, 0, 0);
    windowManager.createWindow("Move Forwards TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 441; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -10; i <= 10; i++) {
            for (float j = -10; j <= 10; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i, 0.0f, j);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can move forwards");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(Player, PlayerMoveLeft) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, false, false, true, 0, 0, 0);
    windowManager.createWindow("Move Left TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 441; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -10; i <= 10; i++) {
            for (float j = -10; j <= 10; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i, 0.0f, j);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can move left");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(Player, PlayerMoveRight) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, false, false, false, true, 0, 0);
    windowManager.createWindow("Move Right TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 441; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -10; i <= 10; i++) {
            for (float j = -10; j <= 10; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i, 0.0f, j);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can move right");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(Player, PlayerMoveBack) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, false, true, false, false, 0, 0);
    windowManager.createWindow("Move Back TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 441; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -10; i <= 10; i++) {
            for (float j = -10; j <= 10; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i, 0.0f, j);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can move back");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(Player, PlayerMoveDiagonal) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, true, true, true, 0, 0);
    windowManager.createWindow("Move Diagonal TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 441; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -10; i <= 10; i++) {
            for (float j = -10; j <= 10; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i, 0.0f, j);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can move diagonally");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(Player, PlayerLook) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, false, false, false, false, true, 0);
    windowManager.createWindow("Rotate Camera TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 441; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -10; i <= 10; i++) {
            for (float j = -10; j <= 10; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i, 0.0f, j);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can rotate camera");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(Player, PlayerMoveWithLook) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, false, true, true, true, true, true, 0);
    windowManager.createWindow("Move Relative to Camera TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 441; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -10; i <= 10; i++) {
            for (float j = -10; j <= 10; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i, 0.0f, j);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can move relative to camera");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}

TEST(Player, PlayerSprint) {
    SDLWindowManager windowManager = SDLWindowManager(false, true, true, true, true, true, true, true, 0);
    windowManager.createWindow("Sprint TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        for (uint32_t i = 0; i < 441; i++) {
            i_world->createEntity();
        }
        i_world->registerComponentType(BlockComponents::getComponentID());
        i_world->registerComponentType(BlockTextureComponent::getComponentID());
        i_world->registerComponentType(TransformComponents::getComponentID());
        SetPositionSystem ms;
        for (float i = -10; i <= 10; i++) {
            for (float j = -10; j <= 10; j++) {
                std::vector<float> args;
                ms.i_pos = ngl::Vec3(i, 0.0f, j);
                i_world->run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
            }
        }
        ApplyBlockTextureSystem applyBlockTextureSystem;
        applyBlockTextureSystem.i_blockType = BlockType::Grass;
        i_world->run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

        utils::printTestString("player can sprint");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}