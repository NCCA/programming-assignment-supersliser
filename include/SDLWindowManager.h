//
// Created by s5605187 on 15/04/25.
//

#ifndef COLONYMANAGERBUILD_SDLWINDOWMANAGER_H
#define COLONYMANAGERBUILD_SDLWINDOWMANAGER_H

#include <SDL2/SDL.h>
#include <ngl/Vec2.h>
#include "Table.h"
#include "Utils.h"
#include "component/IsSprintingComponent.h"
#include "system/SetSprintingSystem.h"
#include "component/CameraComponents.h"
#include "system/RotateCameraSystem.h"
#include "system/RenderWorldSystem.h"
#include "system/MovePlayerSystem.h"
#include "system/SetPlayerPositionSystem.h"
#include "system/PlayerFallSystem.h"


/// @class SDLWindowManager include/SDLWindowManager.h
/// @brief Manages the SDL window and handles events
/// @details This class is responsible for creating the SDL window, handling events, and managing the game loop.
/// @author Thomas Lower
/// @date 2025/04/15
/// @version 1.0
class SDLWindowManager {
    /// @brief SDL window pointer
    SDL_Window *m_window;
    /// @brief SDL OpenGL context
    SDL_GLContext m_glContext;
    /// @brief World Table
    Table m_world;

    std::vector<Table> m_chunkedWorld;
    /// @brief Player Table
    Table m_players;

    /// @brief Window is running
    bool m_isRunning;
    /// @brief Window is fullscreen
    bool m_isFullscreen;
    /// @brief Window is visible
    bool m_isVisible;
    /// @brief Control W key enabled
    bool m_controlWEnabled;
    /// @brief Control S key enabled
    bool m_controlSEnabled;
    /// @brief Control A key enabled
    bool m_controlAEnabled;
    /// @brief Control D key enabled
    bool m_controlDEnabled;
    /// @brief Mouse control enabled
    bool m_mouseControlEnabled;
    /// @brief Sprint enabled
    bool m_sprintEnabled;
    /// @brief Player can fall
    bool m_canFall;

    /// @brief Spawn point for the player
    ngl::Vec3 m_spawnPoint;
public:
    /// @creates a window
    /// @param[in] title The title of the window
    void createWindow(const char* title);
    /// @brief Begins the event loop
    /// @returns true if the loop is ended by pressing enter, otherwise returns false
    bool runEvents();

    bool runEventsWithChunking();
    /// @brief Handles the movement of the player
    /// @param[in] dir The direction of the movement
    /// @param[in] deltaTime The time since the last frame
    void walk(ngl::Vec2 dir, int32_t deltaTime);
    /// @brief Destructor
    ~SDLWindowManager();
    /// @brief Constructor
    /// @param[in] i_fullscreen If true, the window will be fullscreen
    /// @param[in] i_visible If true, the window will be visible
    /// @param[in] i_sprint If true, the player will sprint
    /// @param[in] i_controlW If true, the W key will be used for movement
    /// @param[in] i_controlS If true, the S key will be used for movement
    /// @param[in] i_controlA If true, the A key will be used for movement
    /// @param[in] i_controlD If true, the D key will be used for movement
    /// @param[in] i_mouseControl If true, the mouse will be used for movement
    /// @param[in] i_canFall If true, the player can fall
    /// @param[in] i_spawnPoint The spawn point of the player
    /// @details The constructor initializes the SDL window and OpenGL context, and sets up the world and player tables.
    /// @details The constructor also sets up the event loop and handles the movement of the player.
    /// @details The constructor also sets up the camera and rendering systems.
    /// @details The constructor also sets up the player fall system and the sprinting system.
    explicit SDLWindowManager(bool i_fullscreen = false, bool i_visible = true, bool i_sprint = false,
                     bool i_controlW = false, bool i_controlS = false, bool i_controlA = false,
                     bool i_controlD = false, bool i_mouseControl = false, bool i_canFall = false, ngl::Vec3 i_spawnPoint = ngl::Vec3(0, 2, 0));

    std::function<void(Table* io_world, Table* i_players)> generateWorld;
    std::function<void(std::vector<Table>* io_chunkedWorld, Table* io_chunks, Table* i_players)> generateChunkedWorld;

    bool isMIsRunning() const {
        return m_isRunning;
    }

    void setMIsRunning(bool mIsRunning) {
        m_isRunning = mIsRunning;
    }

    bool isMIsFullscreen() const {
        return m_isFullscreen;
    }

    void setMIsFullscreen(bool mIsFullscreen) {
        m_isFullscreen = mIsFullscreen;
    }

    bool isMIsVisible() const {
        return m_isVisible;
    }

    void setMIsVisible(bool mIsVisible) {
        m_isVisible = mIsVisible;
    }

    bool isMControlWEnabled() const {
        return m_controlWEnabled;
    }

    void setMControlWEnabled(bool mControlWEnabled) {
        m_controlWEnabled = mControlWEnabled;
    }

    bool isMControlSEnabled() const {
        return m_controlSEnabled;
    }

    void setMControlSEnabled(bool mControlSEnabled) {
        m_controlSEnabled = mControlSEnabled;
    }

    bool isMControlAEnabled() const {
        return m_controlAEnabled;
    }

    void setMControlAEnabled(bool mControlAEnabled) {
        m_controlAEnabled = mControlAEnabled;
    }

    bool isMControlDEnabled() const {
        return m_controlDEnabled;
    }

    void setMControlDEnabled(bool mControlDEnabled) {
        m_controlDEnabled = mControlDEnabled;
    }

    bool isMMouseControlEnabled() const {
        return m_mouseControlEnabled;
    }

    void setMMouseControlEnabled(bool mMouseControlEnabled) {
        m_mouseControlEnabled = mMouseControlEnabled;
    }

    bool isMSprintEnabled() const {
        return m_sprintEnabled;
    }

    void setMSprintEnabled(bool mSprintEnabled) {
        m_sprintEnabled = mSprintEnabled;
    }

};

#endif //COLONYMANAGERBUILD_SDLWINDOWMANAGER_H
