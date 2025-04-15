//
// Created by thoma on 29/03/2025.
//

#ifndef UTILS_H
#define UTILS_H
#include <SDL_video.h>
#include <string>

/// @file Utils.h
/// @brief Contains utility functions for SDL and testing output.
namespace utils
{
    /// @brief Creates an OpenGL context for the given SDL window.
    /// @param window The SDL window to create the context for.
    /// @return The created OpenGL context.
    SDL_GLContext createOpenGLContext(SDL_Window *window);
    /// @brief Convets a number to its string representation.
    /// @param i_num The number to convert.
    /// @return The string representation of the number.
    /// @details This function converts a number to its string representation.\nFor Example, 0 -> "Zero", 1 -> "One", etc.
    char numToString(uint8_t i_num);
    /// @brief Prints a test string to the console.
    /// @param i_testTitle The title of the test
    void printTestString(const std::string &i_testTitle);
    /// @brief Formats a string with terminal colour control
    /// @param i_text The text to format.
    /// @param i_textColour The text colour to use.
    /// @param i_backgroundColour The background colour to use.
    /// @return The formatted string.
    std::string colourTerminalText(const std::string &i_text, const std::string &i_textColour, const std::string &i_backgroundColour);
}

#endif //UTILS_H
