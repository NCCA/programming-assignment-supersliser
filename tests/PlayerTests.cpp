//
// Created by thoma on 29/03/2025.
//

#include <component/CameraComponents.h>
#include <SDL2/SDL.h>
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>

#include "Table.h"
#include "utils.h"
#include "component/BlockComponents.h"
#include "component/BlockTextureComponent.h"
#include "system/ApplyBlockTextureSystem.h"
#include "system/MovePlayerSystem.h"
#include "system/MoveSystem.h"
#include "system/RenderWorldSystem.h"
#include "system/RotateCameraSystem.h"
#include "system/SetSprintingSystem.h"
#include "system/ToggleSprintingSystem.h"
#include "system/SetPositionSystem.h"

TEST(Player, PlayerMoveForwards)
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Player Move Forwards TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_vao = static_cast<BlockTextureComponent*>(world.getColumn(world.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaos;
    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    players.registerComponentType(SpeedComponent::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            wHeld = false;

                            break;
                    }
                }
                    break;
                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_w:
                            wHeld = true;
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    } // end of key process
                } // end of keydown
                default:
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

TEST(Player, PlayerMoveLeft) {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Player Move Left TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_vao = static_cast<BlockTextureComponent*>(world.getColumn(world.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaos;

    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    players.registerComponentType(SpeedComponent::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool aHeld = false;

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (aHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_a:
                            aHeld = false;
                            break;
                    }
                }
                    break;
                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_a:
                            aHeld = true;
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    } // end of key process
                } // end of keydown
                default:
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

TEST(Player, PlayerMoveRight) {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Player Move Right TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_vao = static_cast<BlockTextureComponent*>(world.getColumn(world.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaos;

    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }

    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    players.registerComponentType(SpeedComponent::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool dHeld = false;

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (dHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_d:
                            dHeld = false;
                            break;
                    }
                }
                    break;
                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_d:
                            dHeld = true;
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    } // end of key process
                } // end of keydown
                default:
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

TEST(Player, PlayerMoveBack) {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Player Move Back TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_vao = static_cast<BlockTextureComponent*>(world.getColumn(world.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaos;

    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }

    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    players.registerComponentType(SpeedComponent::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool sHeld = false;

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (sHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_s:
                            sHeld = false;
                            break;
                    }
                }
                    break;
                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_s:
                            sHeld = true;
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    } // end of key process
                } // end of keydown
                default:
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

TEST(Player, PlayerMoveDiagonal) {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Player Move Diagonal TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_vao = static_cast<BlockTextureComponent*>(world.getColumn(world.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaos;

    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }

    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    players.registerComponentType(SpeedComponent::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool dHeld = false;
    bool aHeld = false;
    bool sHeld = false;

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (sHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (wHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (aHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (dHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }



        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_s:
                            sHeld = false;
                            break;
                        case SDLK_w:
                            wHeld = false;
                            break;
                        case SDLK_a:
                            aHeld = false;
                            break;
                        case SDLK_d:
                            dHeld = false;
                        break;
                    }
                }
                    break;
                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_s:
                            sHeld = true;
                            break;
                    case SDLK_w:
                        wHeld = true;
                        break;
                    case SDLK_a:
                        aHeld = true;
                        break;
                    case SDLK_d:
                        dHeld = true;
                        break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    } // end of key process
                } // end of keydown
                default:
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

TEST(Player, PlayerLook) {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Player Look TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }


    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_vao = static_cast<BlockTextureComponent*>(world.getColumn(world.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaos;

    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }

    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION:
                    {
                        RotateCameraSystem rotateCameraSystem;
                        rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                        players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                    }
                    break;
                // this is the window x being clicked.
            case SDL_MOUSEBUTTONDOWN:
                {
                    SDL_CaptureMouse(SDL_TRUE);
                    SDL_ShowCursor(SDL_DISABLE);
                }
                break;
                case SDL_QUIT:
                    quit = true;
                    break;
                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    } // end of key process
                } // end of keydown
                default:
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

TEST(Player, PlayerMoveWithLook) {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Player Move With Look TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_vao = static_cast<BlockTextureComponent*>(world.getColumn(world.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaos;

    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }

    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    players.registerComponentType(SpeedComponent::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool dHeld = false;
    bool aHeld = false;
    bool sHeld = false;

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (sHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (wHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (aHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (dHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }



        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEMOTION:
                {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    SDL_CaptureMouse(SDL_TRUE);
                    SDL_ShowCursor(SDL_DISABLE);
                }
                break;
                // this is the window x being clicked.
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_s:
                            sHeld = false;
                            break;
                        case SDLK_w:
                            wHeld = false;
                            break;
                        case SDLK_a:
                            aHeld = false;
                            break;
                        case SDLK_d:
                            dHeld = false;
                        break;
                    }
                }
                    break;
                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_s:
                            sHeld = true;
                            break;
                    case SDLK_w:
                        wHeld = true;
                        break;
                    case SDLK_a:
                        aHeld = true;
                        break;
                    case SDLK_d:
                        dHeld = true;
                        break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    } // end of key process
                } // end of keydown
                default:
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

TEST(Player, PlayerSprint)
{
        // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("Player Sprint TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_vao = static_cast<BlockTextureComponent*>(world.getColumn(world.getComponentIndex(BlockTextureComponent::getComponentID())).get())->m_vaos;

    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }

    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    players.registerComponentType(IsSprintingComponent::getComponentID());
    players.registerComponentType(SpeedComponent::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool dHeld = false;
    bool aHeld = false;
    bool sHeld = false;

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (sHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent*>(players.getColumn(players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (wHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent*>(players.getColumn(players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (aHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent*>(players.getColumn(players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (dHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent*>(players.getColumn(players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }



        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEMOTION:
                {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    SDL_CaptureMouse(SDL_TRUE);
                    SDL_ShowCursor(SDL_DISABLE);
                }
                break;
                // this is the window x being clicked.
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_LSHIFT:
                            {
                                SetSprintingSystem t;
                                t.i_value = false;
                                players.run(&t, IsSprintingComponent::getComponentID());
                            }
                                break;
                        case SDLK_s:
                            sHeld = false;
                            break;
                        case SDLK_w:
                            wHeld = false;
                            break;
                        case SDLK_a:
                            aHeld = false;
                            break;
                        case SDLK_d:
                            dHeld = false;
                        break;
                    }
                }
                    break;
                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_LSHIFT:
                            {
                                SetSprintingSystem t;
                                t.i_value = true;
                                players.run(&t, IsSprintingComponent::getComponentID());
                            }
                        break;
                        // if it's the escape key quit
                        case SDLK_s:
                            sHeld = true;
                            break;
                    case SDLK_w:
                        wHeld = true;
                        break;
                    case SDLK_a:
                        aHeld = true;
                        break;
                    case SDLK_d:
                        dHeld = true;
                        break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    } // end of key process
                } // end of keydown
                default:
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