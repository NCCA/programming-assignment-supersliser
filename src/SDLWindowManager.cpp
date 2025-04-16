//
// Created by s5605187 on 15/04/25.
//

#include "SDLWindowManager.h"
#include "component/BlockComponents.h"
#include "component/BlockTextureComponent.h"


void SDLWindowManager::createWindow(const char* title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL");
        return;
    }
    m_window = SDL_CreateWindow(title,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                1080,
                                720,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!m_window)
    {
        printf("Unable to create window");
        return;
    }
    m_glContext =  utils::createOpenGLContext(m_window);
    if (!m_glContext)
    {
        printf("Problem creating OpenGL context ");
        return;
    }
    SDL_GL_MakeCurrent(m_window, m_glContext);
    SDL_GL_SetSwapInterval(1);
    ngl::NGLInit::initialize();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(m_window);
}

bool SDLWindowManager::runEvents()
{
    if (generateWorld == nullptr)
    {
        std::cerr << "No world generation function provided" << std::endl;
        return false;
    }
    int32_t lastTime = SDL_GetTicks();

    bool wHeld = false;
    bool sHeld = false;
    bool aHeld = false;
    bool dHeld = false;

    m_players = Table();
    m_players.createEntity();
    m_players.registerComponentType(CameraComponents::getComponentID());
    m_players.registerComponentType(IsSprintingComponent::getComponentID());
    m_players.registerComponentType(SpeedComponent::getComponentID());
    SetPlayerPositionSystem setPlayerPositionSystem;
    setPlayerPositionSystem.i_pos = ngl::Vec4(m_spawnPoint.m_x, m_spawnPoint.m_y, m_spawnPoint.m_z, 0.0f);
    m_players.run(&setPlayerPositionSystem, CameraComponents::getComponentID());
    m_world = Table();
    m_world.createEntity();
    generateWorld(&m_world, &m_players);

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &m_world;

    PlayerFallSystem playerFallSystem;
    playerFallSystem.i_world = &m_world;
    playerFallSystem.i_speed = static_cast<SpeedComponent*>(m_players.getColumn(
            m_players.getComponentIndex(SpeedComponent::getComponentID())).get());

    std::function render = [&]() {
        m_players.run(&renderWorldSystem, CameraComponents::getComponentID());
    };

    if (m_canFall) {
        render = [&]() {
            m_players.run(&playerFallSystem, CameraComponents::getComponentID());
            m_players.run(&renderWorldSystem, CameraComponents::getComponentID());
        };
    }

    while (m_isRunning) {
        int32_t currentTime = SDL_GetTicks();
        int32_t deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (wHeld) { walk(ngl::Vec2(0, 1), deltaTime); }
        if (sHeld) { walk(ngl::Vec2(0, -1), deltaTime); }
        if (aHeld) { walk(ngl::Vec2(1, 0), deltaTime); }
        if (dHeld) { walk(ngl::Vec2(-1, 0), deltaTime); }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    m_isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        m_isRunning = false;
                        return false;
                    }
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        m_isRunning = false;
                        return true;
                    }
                    if (event.key.keysym.sym == SDLK_w && m_controlWEnabled) {
                        wHeld = true;
                    }
                    if (event.key.keysym.sym == SDLK_s && m_controlSEnabled) {
                        sHeld = true;
                    }
                    if (event.key.keysym.sym == SDLK_a && m_controlAEnabled) {
                        aHeld = true;
                    }
                    if (event.key.keysym.sym == SDLK_d && m_controlDEnabled) {
                        dHeld = true;
                    }
                    if (event.key.keysym.sym == SDLK_LSHIFT && m_sprintEnabled) {
                        SetSprintingSystem t;
                        t.i_value = true;
                        m_players.run(&t, IsSprintingComponent::getComponentID());
                    }
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_w && m_controlWEnabled) {
                        wHeld = false;
                    }
                    if (event.key.keysym.sym == SDLK_s && m_controlSEnabled) {
                        sHeld = false;
                    }
                    if (event.key.keysym.sym == SDLK_a && m_controlAEnabled) {
                        aHeld = false;
                    }
                    if (event.key.keysym.sym == SDLK_d && m_controlDEnabled) {
                        dHeld = false;
                    }
                    if (event.key.keysym.sym == SDLK_LSHIFT) {
                        SetSprintingSystem t;
                        t.i_value = false;
                        m_players.run(&t, IsSprintingComponent::getComponentID());
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (m_mouseControlEnabled) {
                        RotateCameraSystem rotateCameraSystem;
                        rotateCameraSystem.i_mouseDelta = ngl::Vec2(event.motion.xrel, event.motion.yrel);
                        m_players.run(&rotateCameraSystem, CameraComponents::getComponentID());
                    }
                    break;
                default:
                    break;
            }
        }
        render();
        SDL_GL_SwapWindow(m_window);
    }
    return false;
}

void SDLWindowManager::walk(ngl::Vec2 dir, int32_t deltaTime)
{
    MovePlayerSystem playerMoveSystem;

    playerMoveSystem.i_isSprinting = static_cast<IsSprintingComponent *>(m_players.getColumn(
            m_players.getComponentIndex(IsSprintingComponent::getComponentID())).get());
    playerMoveSystem.i_dir = ngl::Vec3(dir.m_x * deltaTime, 0.0f, dir.m_y * deltaTime);
    playerMoveSystem.i_world = &m_world;
    playerMoveSystem.i_speed = static_cast<SpeedComponent *>(m_players.getColumn(
            m_players.getComponentIndex(SpeedComponent::getComponentID())).get());
    m_players.run(&playerMoveSystem, CameraComponents::getComponentID());
}

SDLWindowManager::SDLWindowManager(bool i_fullscreen, bool i_visible, bool i_sprint, bool i_controlW, bool i_controlS,
                                   bool i_controlA, bool i_controlD, bool i_mouseControl, bool i_canFall, ngl::Vec3 i_spawnPoint) {
    m_isRunning = true;
    m_isFullscreen = i_fullscreen;
    m_isVisible = i_visible;
    m_controlWEnabled = i_controlW;
    m_controlSEnabled = i_controlS;
    m_controlAEnabled = i_controlA;
    m_controlDEnabled = i_controlD;
    m_mouseControlEnabled = i_mouseControl;
    m_sprintEnabled = i_sprint;
    m_canFall = i_canFall;
    m_spawnPoint = i_spawnPoint;
}

SDLWindowManager::~SDLWindowManager()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}