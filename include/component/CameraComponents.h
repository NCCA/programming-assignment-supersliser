//
// Created by thoma on 24/03/2025.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include <ngl/Mat4.h>
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include "Camera.h"

/// @class CameraComponents include/component/CameraComponents.h
/// @brief Class to define a generic entity as a camera
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-24
/// @note A Camera is an alias for a player as this game is designed to be single player, therefore, will only be rendered from the 1 player's first person perspective.
class CameraComponents
{
    public:
    /// @brief Constructor
    /// @param[in] i_size number of entities in parent table
    explicit CameraComponents(size_t i_size);
    /// @brief Vector of cameras
    /// @detail Each index of the vector corresponds to a seperate entity
    /// @note The component stores a vector of cameras for semantic compatibility with other components even though it should never have more than 1 entity.
    std::vector<Camera> m_cameras;
    /// @brief Static function to get the camera ID
    /// @return component ID: 4
    static std::uint8_t getComponentID() { return 4; }
    /// @brief Default Destructor
    ~CameraComponents();
};

#endif //CAMERACOMPONENT_H
