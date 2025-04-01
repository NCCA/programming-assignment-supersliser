//
// Created by thoma on 31/03/2025.
//

#ifndef SPEEDCOMPONENT_H
#define SPEEDCOMPONENT_H

#include <vector>
#include <cstdint>

class SpeedComponent
{
public:
    std::vector<float> m_speed;
    static std::uint8_t getComponentID() { return 7; }
    static float getDefaultSpeed() { return 0.005f; }
    SpeedComponent(size_t size);
    ~SpeedComponent() = default;
};

#endif //SPEEDCOMPONENT_H
