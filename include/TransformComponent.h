//
// Created by tom on 3/21/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <ngl/Vec3.h>
#include <ngl/Quaternion.h>
#include "Component.h"

class TransformComponent : public a_Component {
public:
	ngl::Vec3 m_p;
    ngl::Quaternion m_r;
    ngl::Vec3 m_s;
};

#endif //TRANSFORMCOMPONENT_H
