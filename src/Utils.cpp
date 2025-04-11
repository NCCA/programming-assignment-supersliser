//
// Created by thoma on 29/03/2025.
//

#include "Utils.h"

#include <fmt/format.h>

SDL_GLContext utils::createOpenGLContext(SDL_Window* window)
{
    // Note you may have to change this depending upon the driver (Windows is fussy)
    // stick to 4.5 as the core base level for NGL works ok
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // set multi sampling else we get really bad graphics that alias
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    // on mac up to 32 will work but under linux centos build only 16
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // enable double buffering (should be on by default)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //
    return SDL_GL_CreateContext(window);
}

char utils::numToString(uint8_t i_num)
{
    char output = 64 + i_num;
    return output;
}

void utils::printTestString(const std::string& i_testTitle)
{
    printf(colourTerminalText("\n|---------------------------------------------|\n", "0;37", "0;40").c_str());
    printf(colourTerminalText(fmt::format("  Testing {}\n", i_testTitle).c_str(), "0;37", "0;40").c_str());
    printf(colourTerminalText("  Press ENTER to pass test\n", "0;32", "0;40").c_str());
    printf(colourTerminalText("  Press ESC to fail test\n", "0;31", "0;40").c_str());
    printf(colourTerminalText("|---------------------------------------------|\n", "0;37", "0;40").c_str());
}

std::string utils::colourTerminalText(const std::string& i_text, const std::string& i_textColour, const std::string& i_backgroundColour)
{
    std::string text = fmt::format("\033[{};{}m{}\033[0m", i_textColour, i_backgroundColour, i_text);
    return text;
}