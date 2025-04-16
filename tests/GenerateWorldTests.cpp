//
// Created by s5605187 on 06/04/25.
//

#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <ngl/NGLInit.h>

#include "GenerateWorld.h"
#include "Table.h"
#include "Utils.h"
#include "system/RenderWorldSystem.h"
#include "system/MovePlayerSystem.h"
#include "system/RotateCameraSystem.h"
#include "system/PlayerFallSystem.h"
#include "system/SetPlayerPositionSystem.h"
#include "SDLWindowManager.h"
#include "GenerateWorld.h"

TEST(GenerateWorld, generateWorld)
{
    SDLWindowManager windowManager = SDLWindowManager(false, true, true, true, true, true, true, true, 1, ngl::Vec3(0, 20, 0));
    windowManager.createWindow("World Generator TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        generateWorld(i_world, 10, 20, 10, 0);
        utils::printTestString("world will generate");
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}
