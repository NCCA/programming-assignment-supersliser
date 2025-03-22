//
// Created by tom on 3/21/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <ngl/Vec3.h>
#include <ngl/Quaternion.h>

class PositonComponent {
public:
    PositonComponent(size_t i_size);
    std::vector<ngl::Vec3> m_ps;
    static std::uint8_t getComponentID() { return 2;}
};

#endif //TRANSFORMCOMPONENT_H
