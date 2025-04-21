//
// Created by thoma on 11/04/2025.
//

#include <SDL.h>
#include <GL/gl3w.h>
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>

#include "Utils.h"
#include "SDLWindowManager.h"
#include "GenerateWorld.h"

/// @brief Tests that an SDL window with OpenGL can be created and displayed
/// @result Success if the user presses ENTER after entering the event loop after the window has been displayed, otherwise fails
TEST(SDLTest, WindowVisible)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Is this window visible?",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window) {
        printf("Unable to create window");
        return;
    }

    bool quit = false;
    SDL_Event event;
    bool success = false;

    while (!quit) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    quit = true;
                    break;
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE :
                            quit = true;
                            break;
                        case SDLK_RETURN :
                            success = true;
                            quit = true;
                            break;
                        default :
                            break;
                    }
                }
                    break;
                default :
                    break;
            }
        }
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

/// @brief Tests the SDLWindowManager can be created and can contain a window
TEST(SDLTest, SDLWindowManagerTest) {
    SDLWindowManager windowManager = SDLWindowManager();
    windowManager.createWindow("SDL Window Manager Test");
    EXPECT_TRUE(windowManager.isMIsRunning());
    EXPECT_FALSE(windowManager.isMIsFullscreen());
    EXPECT_TRUE(windowManager.isMIsVisible());
    EXPECT_FALSE(windowManager.isMControlWEnabled());
    EXPECT_FALSE(windowManager.isMControlSEnabled());
    EXPECT_FALSE(windowManager.isMControlAEnabled());
    EXPECT_FALSE(windowManager.isMControlDEnabled());
    EXPECT_FALSE(windowManager.isMMouseControlEnabled());
    EXPECT_FALSE(windowManager.isMSprintEnabled());

    windowManager.setMIsRunning(false);
    windowManager.setMIsFullscreen(true);
    windowManager.setMIsVisible(false);
    windowManager.setMControlWEnabled(true);
    windowManager.setMControlSEnabled(true);
    windowManager.setMControlAEnabled(true);
    windowManager.setMControlDEnabled(true);
    windowManager.setMMouseControlEnabled(true);
    windowManager.setMSprintEnabled(true);

    EXPECT_FALSE(windowManager.isMIsRunning());
    EXPECT_TRUE(windowManager.isMIsFullscreen());
    EXPECT_FALSE(windowManager.isMIsVisible());
    EXPECT_TRUE(windowManager.isMControlWEnabled());
    EXPECT_TRUE(windowManager.isMControlSEnabled());
    EXPECT_TRUE(windowManager.isMControlAEnabled());
    EXPECT_TRUE(windowManager.isMControlDEnabled());
    EXPECT_TRUE(windowManager.isMMouseControlEnabled());
    EXPECT_TRUE(windowManager.isMSprintEnabled());
}

/// @brief Tests the SDLWindowManager can show a world.
TEST(SDLTest, SDLWindowManagerUsage) {
    SDLWindowManager windowManager = SDLWindowManager();
    windowManager.createWindow("SDL Window Manager Usage Test");
    windowManager.generateWorld = [](Table* io_world, Table* i_players) {
        generateWorld(io_world, 5, 5, 5, 666);
    };
    auto output = windowManager.runEvents();
    EXPECT_TRUE(output);
}
