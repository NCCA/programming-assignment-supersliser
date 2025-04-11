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

TEST(WorldDisplay, WorldVisible) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("World Visible TEST",
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
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1);
    ngl::NGLInit::initialize();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    bool quit = false;
    SDL_Event event;

    Table players;
    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    Table world;
    for (uint32_t i = 0; i < 1; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_pos = ngl::Vec3(0.0f, 0.0f, 1.0f);
    world.run(&ms, TransformComponents::getComponentID());
    SetCameraLookSystem setCameraLookSystem;
    setCameraLookSystem.i_pos = ngl::Vec3(2.0f, 2.0f, 2.0f);
    setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
    players.run(&setCameraLookSystem, CameraComponents::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;

    utils::printTestString("a single block can be shown");

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

        // now we draw ngl
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        // std::cout << "Running World Visible Test, please press enter if you can see the world or escape otherwise: ";
        // swap the buffers
        SDL_GL_SwapWindow(window);

    }

    EXPECT_TRUE(success);
    // now tidy up and exit SDL
    SDL_Quit();
}


TEST(WorldDisplay, WorldMultiBlockVisible) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("World MultiBlock Visible TEST",
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
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1);
    ngl::NGLInit::initialize();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    bool quit = false;
    SDL_Event event;

    Table players;
    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    Table world;
    for (uint32_t i = 0; i < 9; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -1; i <= 1; i++) {
        for (float j = -1; j <= 1; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i * 1, 0.0f, j * 1);
            world.run(&ms, TransformComponents::getComponentID(), (i + 1) * 3 + (j + 1), (i + 1) * 3 + (j + 1));
        }
    }

    SetCameraLookSystem setCameraLookSystem;
    setCameraLookSystem.i_pos = ngl::Vec3(4.0f, 4.0f, 4.0f);
    setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
    players.run(&setCameraLookSystem, CameraComponents::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());
    for (float i = -1; i <= 1; i++) {
        for (float j = -1; j <= 1; j++) {
            world.createEntity();
            ms.i_pos = ngl::Vec3(i * 1, -1.0f, j * 1);
            world.run(&ms, TransformComponents::getComponentID(), 9 + (i + 1) * 3 + (j + 1), 9 + (i + 1) * 3 + (j + 1));
        }
    }
    applyBlockTextureSystem.i_blockType = BlockType::Dirt;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), 9, 18);

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;

    utils::printTestString("multiple blocks can be shown");

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

        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);

    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(WorldDisplay, AllTextureTest) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("All Texture TEST",
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
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1);
    ngl::NGLInit::initialize();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    bool quit = false;
    SDL_Event event;

    constexpr int TEXTURE_COUNT = 7;

    Table players;
    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());

    Table world;
    for (uint32_t i = 0; i < TEXTURE_COUNT; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;

    SetCameraLookSystem setCameraLookSystem;
    setCameraLookSystem.i_pos = ngl::Vec3(4.0f, 4.0f, 4.0f);
    setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
    players.run(&setCameraLookSystem, CameraComponents::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    for (int i = 0; i < TEXTURE_COUNT; i++) {
        ms.i_pos = ngl::Vec3(i - TEXTURE_COUNT / 2, 0.0f, 0.0f);
        world.run(&ms, TransformComponents::getComponentID(), i, i);
        applyBlockTextureSystem.i_blockType = static_cast<BlockType>(i);
        world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), i, i);
    }

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

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
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }

    EXPECT_TRUE(success);
    SDL_Quit();
}