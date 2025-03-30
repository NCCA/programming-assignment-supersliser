//
// Created by thoma on 30/03/2025.
//

#ifndef ISSPRINTINGCOMPONENT_H
#define ISSPRINTINGCOMPONENT_H

#include <vector>
#include <cstdint>


class IsSprintingComponent
{
    public:
  std::vector<bool> m_isSprinting;
  static std::uint8_t getComponentID() { return 6;}

  IsSprintingComponent(size_t size);
  ~IsSprintingComponent() = default;
};

#endif //ISSPRINTINGCOMPONENT_H
