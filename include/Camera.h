//
// Created by tom on 3/20/25.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <ngl/Quaternion.h>
#include <ngl/Vec3.h>

class Camera
{
    protected:
    float m_fov = 90;
    float m_closeCullingDistance = 0.1;
    float m_farCullingDistance = 1000;
    float m_aspectRatio = 1.0;
public:
    void setFov(const float i_fov);
    float fov() const;
    void setAspectRatio(const float i_aspectRatio);
    float aspectRatio() const;
    Camera() = default;
    Camera(const float i_closeCullingDistance, int i_farCullingDistance, float i_fov, float i_aspectRatio);
    void Draw(ngl::Vec3 i_position, ngl::Quaternion i_orientation);
    ~Camera() = default;
};

#endif //CAMERA_H
