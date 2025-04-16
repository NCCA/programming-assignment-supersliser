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

class SDLWindowManager {
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    Table m_world;
    Table m_players;

    bool m_isRunning;
    bool m_isFullscreen;
    bool m_isVisible;
    bool m_controlWEnabled;
    bool m_controlSEnabled;
    bool m_controlAEnabled;
    bool m_controlDEnabled;
    bool m_mouseControlEnabled;
    bool m_sprintEnabled;
    bool m_canFall;

    ngl::Vec3 m_spawnPoint;
public:
    void createWindow(const char* title);
    bool runEvents();
    void walk(ngl::Vec2 dir, int32_t deltaTime);
    ~SDLWindowManager();
    explicit SDLWindowManager(bool i_fullscreen = false, bool i_visible = true, bool i_sprint = false,
                     bool i_controlW = false, bool i_controlS = false, bool i_controlA = false,
                     bool i_controlD = false, bool i_mouseControl = false, bool i_canFall = false, ngl::Vec3 i_spawnPoint = ngl::Vec3(0, 2, 0));
    std::function<void(Table* io_world, Table* i_players)> generateWorld;

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
