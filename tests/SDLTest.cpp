//
// Created by thoma on 11/04/2025.
//

#include <SDL.h>
#include <GL/gl3w.h>
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>

#include "Utils.h"

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
