//
// Created by thoma on 29/03/2025.
//

#ifndef UTILS_H
#define UTILS_H
#include <SDL_video.h>
#include <string>

namespace utils
{
    SDL_GLContext createOpenGLContext(SDL_Window *window);
    char numToString(uint8_t i_num);
}

#endif //UTILS_H
