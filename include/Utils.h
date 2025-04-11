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
    void printTestString(const std::string &i_testTitle);
    std::string colourTerminalText(const std::string &i_text, const std::string &i_textColour, const std::string &i_backgroundColour);
}

#endif //UTILS_H
