//
// Created by s5605187 on 29/03/25.
//

#ifndef COLONYMANAGERBUILD_DIR_H
#define COLONYMANAGERBUILD_DIR_H

#include <cstdlib>
#include <cstring>

/// @brief Get the directory based on the environment variable ENV_LOCATION
/// @return The directory path as a string
/// @note This may only be explicitly needed for use with Clion. But doesn't hurt to be safe.
inline const char* getDir() {
    const char* env_location = std::getenv("ENV_LOCATION");
    if (env_location && std::strcmp(env_location, "home") == 0) {
        return "/home/tom/programming-assignment-supersliser/";
    } else if (env_location && std::strcmp(env_location, "university") == 0) {
        return "/home/s5605187/Documents/programming-assignment-supersliser/";
    } else {
        throw std::runtime_error("Unknown environment. Please set ENV_LOCATION to 'home' or 'university'.");
    }
}

#endif //COLONYMANAGERBUILD_DIR_H
