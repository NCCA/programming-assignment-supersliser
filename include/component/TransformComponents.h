//
// Created by tom on 3/21/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <ngl/Vec3.h>
#include <ngl/Quaternion.h>

/// @class TransformComponents include/component/TransformComponents.h
/// @brief Component column to store the positions of entities
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-21
class TransformComponents {
public:
    /// @brief Constructor
    /// @param[in] i_size number of entities in parent table
    TransformComponents(size_t i_size, std::shared_ptr<GLuint> i_vaoID);
    /// @brief Vector of positions
    /// @detail Each index of the vector corresponds to a separate entity
    std::vector<ngl::Vec3> m_ps;
    /// @brief Pointer to the position VBO ID
    /// @detail This is used to allow the positions to be added to the shader as instances.
    std::shared_ptr<GLuint> m_positionVboId;
    /// @brief Static function to get the component ID
    /// @return component ID: 2
    static std::uint8_t getComponentID() { return 2;}
    /// @brief Adds an entity to the component
    void addEntity();

    std::shared_ptr<GLuint> m_vaoID;

};

#endif //TRANSFORMCOMPONENT_H
