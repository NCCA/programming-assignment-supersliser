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
    std::shared_ptr<GLuint> m_positionVboId;
    static std::uint8_t getComponentID() { return 2;}
    void addEntity();
};

#endif //TRANSFORMCOMPONENT_H
