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

TEST(GenerateWorld, generateWorld)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window* window = SDL_CreateWindow("Player Generate World TEST",
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
    SetPlayerPositionSystem setPlayerPositionSystem;
    setPlayerPositionSystem.i_pos = ngl::Vec4(0.0f, 20.0f, 0.0f, 0.0f);
    players.run(&setPlayerPositionSystem, CameraComponents::getComponentID());

    Table world;
    generateWorld(&world, 20, 20, 20, 0);
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
    bool aHeld = false;
    bool dHeld = false;

    utils::printTestString("generating a world");

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

        if (aHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(deltaTime, 0.0f, 0.0f);
            playerMoveSystem.i_world = &world;
            playerMoveSystem.i_speed = static_cast<SpeedComponent*>(players.getColumn(
                players.getComponentIndex(SpeedComponent::getComponentID())).get());
            players.run(&playerMoveSystem, CameraComponents::getComponentID());
        }

        if (dHeld)
        {
            MovePlayerSystem playerMoveSystem;
            playerMoveSystem.i_dir = ngl::Vec3(-deltaTime, 0.0f, 0.0f);
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
                    case SDLK_a:
                        aHeld = false;
                        break;
                    case SDLK_d:
                        dHeld = false;
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

        players.run(&playerFallSystem, CameraComponents::getComponentID());
        players.run(&renderWorldSystem, CameraComponents::getComponentID());

        SDL_GL_SwapWindow(window);
    }

    EXPECT_TRUE(success);
    // now tidy up and exit SDL
    SDL_Quit();
}
