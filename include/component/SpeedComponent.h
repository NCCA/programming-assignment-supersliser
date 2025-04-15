//
// Created by thoma on 31/03/2025.
//

#ifndef SPEEDCOMPONENT_H
#define SPEEDCOMPONENT_H

#include <vector>
#include <cstdint>

/// @class SpeedComponent include/component/SpeedComponent.h
/// @brief Components for each entities speed
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-31
class SpeedComponent
{
public:
  /// @brief Vector of speeds
    std::vector<float> m_speed;
    /// @brief Static function to get the component ID
    /// @return component ID: 7
    static std::uint8_t getComponentID() { return 7; }
    /// @brief Static function to get the default speed
    /// @return default speed: 0.003f
    static float getDefaultSpeed() { return 0.003f; }
    /// @brief Constructor
    /// @param[in] i_size number of entities in parent table
    SpeedComponent(size_t size);
    /// @brief Default Destructor
    ~SpeedComponent() = default;
};

#endif //SPEEDCOMPONENT_H
