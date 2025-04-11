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

TEST(Player, PlayerMoveForwards) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Player Move Forwards TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
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
    players.registerComponentType(SpeedComponent::getComponentID());

    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;

    utils::printTestString("player can move forwards");

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
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
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
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
                    }
                }
                default:
                    break;
            }
        }
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(Player, PlayerMoveLeft) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Player Move Left TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
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
    players.registerComponentType(SpeedComponent::getComponentID());
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;

    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool aHeld = false;

    utils::printTestString("player can move left");

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (aHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
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
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
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
                    }
                }
                default:
                    break;
            }
        }
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(Player, PlayerMoveRight) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Player Move Right TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
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
    players.registerComponentType(SpeedComponent::getComponentID());

    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool dHeld = false;

    utils::printTestString("player can move right");

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (dHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
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
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
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
                    }
                }
                default:
                    break;
            }

        }
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(Player, PlayerMoveBack) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Player Move Back TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
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
    players.registerComponentType(SpeedComponent::getComponentID());

    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool sHeld = false;

    utils::printTestString("player can move back");

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (sHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
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
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
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
                    }
                }
                default:
                    break;
            }

        }
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(Player, PlayerMoveDiagonal) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Player Move Diagonal TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
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
    players.registerComponentType(SpeedComponent::getComponentID());
    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
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

    utils::printTestString("player can move diagonal");

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (sHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (wHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (aHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (dHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
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
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
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
                    }
                }
                default:
                    break;
            }

        }
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(Player, PlayerLook) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Player Look TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
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
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;

    utils::printTestString("player can look around");

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION: {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                    break;
                case SDL_MOUSEBUTTONDOWN: {
                    SDL_CaptureMouse(SDL_TRUE);
                    SDL_ShowCursor(SDL_DISABLE);
                }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            success = true;
                            quit = true;
                            break;
                        default:
                            break;
                    }
                }
                default:
                    break;
            }

        }
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(Player, PlayerMoveWithLook) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Player Move With Look TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
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
    players.registerComponentType(SpeedComponent::getComponentID());

    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
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

    utils::printTestString("player can move relative to look direction");

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (sHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (wHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (aHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (dHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent *>(players.getColumn(
                    players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION: {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
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
                    break;
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
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
                    }
                }
                default:
                    break;
            }

        }
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(Player, PlayerSprint) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("Player Sprint TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
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
    players.registerComponentType(IsSprintingComponent::getComponentID());
    players.registerComponentType(SpeedComponent::getComponentID());

    Table world;
    for (uint32_t i = 0; i < 441; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -10; i <= 10; i++) {
        for (float j = -10; j <= 10; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&ms, TransformComponents::getComponentID(), (i + 10) * 21 + (j + 10), (i + 10) * 21 + (j + 10));
        }
    }
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

    utils::printTestString("player can sprint");

    while (!quit) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (sHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent *>(players.getColumn(
                    players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (wHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent *>(players.getColumn(
                    players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (aHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent *>(players.getColumn(
                    players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (dHeld) {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent *>(players.getColumn(
                    players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION: {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                    break;
                case SDL_MOUSEBUTTONDOWN: {
                    SDL_CaptureMouse(SDL_TRUE);
                    SDL_ShowCursor(SDL_DISABLE);
                }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_LSHIFT: {
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
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_LSHIFT: {
                            SetSprintingSystem t;
                            t.i_value = true;
                            players.run(&t, IsSprintingComponent::getComponentID());
                        }
                            break;
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
                    }
                }
                default:
                    break;
            }
        }
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }
    EXPECT_TRUE(success);
    SDL_Quit();
}