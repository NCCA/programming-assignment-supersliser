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
        generateWorld(i_world, 100, 20, 100, 0);
        utils::printTestString("world will generate");
    };
    windowManager.runEvents();
  return EXIT_SUCCESS;
}
