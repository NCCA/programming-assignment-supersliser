//
// Created by tom on 3/21/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <ngl/Vec3.h>
#include <ngl/Quaternion.h>

class TransformComponents {
public:
    TransformComponents(size_t i_size);
    std::vector<ngl::Vec3> m_ps;
    std::vector<ngl::Quaternion> m_rs;
    std::vector<ngl::Vec3> m_ss;
    static std::uint8_t getComponentID() { return 2;}
};

#endif //TRANSFORMCOMPONENT_H
