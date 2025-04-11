//
// Created by thoma on 31/03/2025.
//


#include <SDL2/SDL.h>
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>

#include "Table.h"
#include "utils.h"
#include "component/BlockComponents.h"
#include "component/BlockTextureComponent.h"
#include "component/CameraComponents.h"
#include "system/ApplyBlockTextureSystem.h"
#include "system/MovePlayerSystem.h"
#include "system/PlayerFallSystem.h"
#include "system/RenderWorldSystem.h"
#include "system/RotateCameraSystem.h"
#include "system/SetPositionSystem.h"

TEST(PlayerStep, PlayerStepUp)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window* window = SDL_CreateWindow("Player Step Up TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window)
    {
        printf("Unable to create window");
        return;
    }
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext)
    {
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
    for (uint32_t i = 0; i < 6; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float j = 0; j < 4; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
        world.run(&ms, TransformComponents::getComponentID(), j, j);
    }
    for (float j = 4; j < 6; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, 1.0f, (j - 1));
        world.run(&ms, TransformComponents::getComponentID(), j, j);
    }

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool sHeld = false;

    utils::printTestString("player's ability to step up");

    while (!quit)
    {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (sHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = false;
                        break;
                    case SDLK_s:
                        sHeld = false;
                        break;
                    }
                }
                break;
            case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = true;
                        break;
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

TEST(PlayerStep, PlayerWall)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window* window = SDL_CreateWindow("Player Wall TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window)
    {
        printf("Unable to create window");
        return;
    }
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext)
    {
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
    for (uint32_t i = 0; i < 6; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float j = 0; j < 4; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
        world.run(&ms, TransformComponents::getComponentID(), j, j);
    }
    for (float j = 1; j < 3; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, j, 3.0f);
        world.run(&ms, TransformComponents::getComponentID(), j + 3, j + 3);
    }
    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool sHeld = false;

    utils::printTestString("player stops when hitting a wall");

    while (!quit)
    {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (sHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = false;
                        break;
                    case SDLK_s:
                        sHeld = false;
                        break;
                    }
                }
                break;
            case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                    // if it's the escape key quit
                    case SDLK_w:
                        wHeld = true;
                        break;
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

TEST(PlayerStep, PlayerTopBlockWall)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window* window = SDL_CreateWindow("Player Top Block Wall TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window)
    {
        printf("Unable to create window");
        return;
    }
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext)
    {
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
    for (uint32_t i = 0; i < 6; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float j = 0; j < 4; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
        world.run(&ms, TransformComponents::getComponentID(), j, j);
    }
    for (float j = 1; j < 3; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, j + 1, 3.0f);
        world.run(&ms, TransformComponents::getComponentID(), j + 3, j + 3);
    }
    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool sHeld = false;

    utils::printTestString("player stopping when attempting to step up without space");

    while (!quit)
    {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (sHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = false;
                        break;
                    case SDLK_s:
                        sHeld = false;
                        break;
                    }
                }
                break;
            case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = true;
                        break;
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

TEST(PlayerStep, PlayerBlockedAbove)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window* window = SDL_CreateWindow("Player Blocked Above TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window)
    {
        printf("Unable to create window");
        return;
    }
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext)
    {
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
    for (uint32_t i = 0; i < 6; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float j = 0; j < 4; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
        world.run(&ms, TransformComponents::getComponentID(), j, j);
    }
    ms.i_pos = ngl::Vec3(0.0f, 1, 3.0f);
    world.run(&ms, TransformComponents::getComponentID(), 4, 4);
    ms.i_pos = ngl::Vec3(0.0f, 3, 2.0f);
    world.run(&ms, TransformComponents::getComponentID(), 5, 5);
    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool sHeld = false;

    utils::printTestString("player doesn't from stepping up when blocked above");

    while (!quit)
    {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (sHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = false;
                        break;
                    case SDLK_s:
                        sHeld = false;
                        break;
                    }
                }
                break;
            case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = true;
                        break;
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

TEST(PlayerStep, PlayerStepDown)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window* window = SDL_CreateWindow("Player Step Down TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window)
    {
        printf("Unable to create window");
        return;
    }
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext)
    {
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
    for (uint32_t i = 0; i < 6; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float j = 0; j < 4; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
        world.run(&ms, TransformComponents::getComponentID(), j, j);
    }
    ms.i_pos = ngl::Vec3(0.0f, -1.0f, 3.0f);
    world.run(&ms, TransformComponents::getComponentID(), 4, 4);
    ms.i_pos = ngl::Vec3(0.0f, -1.0f, 4.0f);
    world.run(&ms, TransformComponents::getComponentID(), 5, 5);
    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;
    PlayerFallSystem playerFallSystem;
    playerFallSystem.i_world = &world;
    playerFallSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
        players.getComponentIndex(SpeedComponent::getComponentID())).get());

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool sHeld = false;

    utils::printTestString("player's ability to step down");

    while (!quit)
    {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (sHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = false;
                        break;
                    case SDLK_s:
                        sHeld = false;
                        break;
                    }
                }
                break;
            case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = true;
                        break;
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
        players.run(&playerFallSystem, CameraComponents::getComponentID());
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        SDL_GL_SwapWindow(window);
    }

    EXPECT_TRUE(success);
    SDL_Quit();
}

TEST(PlayerStep, PlayerFallTest)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window* window = SDL_CreateWindow("Player Fall Down TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window)
    {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext)
    {
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
    for (uint32_t i = 0; i < 29; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float j = 0; j < 4; j++)
    {
        ms.i_pos = ngl::Vec3(0.0f, 0.0f, j);
        world.run(&ms, TransformComponents::getComponentID(), j, j);
    }
    for (float x = -2.0f; x < 3.0f; x++)
    {
        for (float z = -2.0f; z < 3.0f; z++)
        {
            ms.i_pos = ngl::Vec3(x, -50.0f, z + 5);
            world.run(&ms, TransformComponents::getComponentID(), (x + 2) * 5 + (z + 2) + 4, (x + 2) * 5 + (z + 2) + 4);
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
    PlayerFallSystem playerFallSystem;
    playerFallSystem.i_world = &world;
    playerFallSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
        players.getComponentIndex(SpeedComponent::getComponentID())).get());

    bool success = false;
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool sHeld = false;

    while (!quit)
    {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (sHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(0.0f, 0.0f, -deltaTime);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                {
                    RotateCameraSystem rotateCameraSystem;
                    rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                    players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                }
                break;
            // this is the window x being clicked.
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        wHeld = false;
                        break;
                    case SDLK_s:
                        sHeld = false;
                        break;
                    }
                }
                break;
            // now we look for a keydown event
            case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                    // if it's the escape key quit
                    case SDLK_w:
                        wHeld = true;
                        break;
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
        players.run(&playerFallSystem, CameraComponents::getComponentID());
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        // std::cout << "Running World Visible Test, please press enter if you can see the world or escape otherwise: ";
        // swap the buffers
        SDL_GL_SwapWindow(window);
    }

    EXPECT_TRUE(success);
    // now tidy up and exit SDL
    SDL_Quit();
}
