//
// Created by thoma on 30/03/2025.
//

#ifndef ISSPRINTINGCOMPONENT_H
#define ISSPRINTINGCOMPONENT_H

#include <vector>
#include <cstdint>

/// @class IsSprintingComponent include/component/IsSprintingComponent.h
/// @brief Component to define whether the player entity is currently sprinting
class IsSprintingComponent
{
public:
  /// @brief vector of booleans to define whether the entity is sprinting
  std::vector<bool> m_isSprinting;
  /// @brief Static function to get the component ID
  /// @return component ID: 6
  static std::uint8_t getComponentID() { return 6;}

  /// @brief Constructor
  /// @param[in] size number of entities in parent table
  IsSprintingComponent(size_t size);
  /// @brief Default Destructor
  ~IsSprintingComponent() = default;
};

#endif //ISSPRINTINGCOMPONENT_H
