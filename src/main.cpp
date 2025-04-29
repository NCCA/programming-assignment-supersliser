#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <ngl/NGLInit.h>
#include "SDLWindowManager.h"
#include "GenerateWorld.h"

void SDLErrorExit(const std::string& _msg);

SDL_GLContext createOpenGLContext(SDL_Window* window);

int main(int argc, char* argv[])
{
    SDLWindowManager windowManager = SDLWindowManager(false, true, true, true, true, true, true, true, 1, ngl::Vec3(0, 20, 0));
    windowManager.createWindow("World Generator TEST");
    windowManager.generateWorld = [](Table* i_world, Table* i_players) {
        //The value here can be up to (100, 20, 100) if in BU Labs
        generateWorld(i_world, 20, 10, 20, 1565614156156);
    };
    windowManager.runEvents();
  return EXIT_SUCCESS;
}
