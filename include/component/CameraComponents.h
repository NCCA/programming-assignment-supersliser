//
// Created by thoma on 24/03/2025.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include <ngl/Mat4.h>

class CameraComponents
{
    public:
    CameraComponents(size_t i_size);
    std::vector<ngl::Mat4> m_view;
    std::vector<ngl::Mat4> m_proj;
    static ngl::Mat4 getDefaultView();
    static ngl::Mat4 getDefaultProj();
    static std::uint8_t getComponentID() { return 4; }
};

#endif //CAMERACOMPONENT_H
