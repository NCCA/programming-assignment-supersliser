//
// Created by thoma on 11/04/2025.
//

#include <SDL.h>
#include <GL/gl3w.h>
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>

#include "utils.h"

TEST(SDLTest, WindowVisible)
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Is this window visible?",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    // make this our current GL context (we can have more than one window but in this case not)
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */// we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    // now clear the screen and swap whilst NGL inits (which may take time)
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    bool success = false;


    while (!quit) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT :
                    quit = true;
                    break;

                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_ESCAPE :
                            quit = true;
                            break;
                        case SDLK_RETURN :
                            success = true;
                            quit = true;
                            break;
                        default :
                            break;
                    } // end of key process
                } // end of keydown

                    break;
                default :
                    break;
            } // end of event switch
        } // end of poll events
    }

    EXPECT_TRUE(success);
    // now tidy up and exit SDL
    SDL_Quit();
}
