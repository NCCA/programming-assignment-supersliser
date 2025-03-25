//
// Created by thoma on 24/03/2025.
//

#include "component/CameraComponents.h"

#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

ngl::Mat4 CameraComponents::getDefaultProj()
{
    return ngl::perspective(45.0f, static_cast<float>(1080) / 720, 0.1f, 200.0f);
}

ngl::Mat4 CameraComponents::getDefaultView()
{
    ngl::Vec3 to(0.0f, 0.0f, 0.0f);
    ngl::Vec3 up(0.0f, 1.0f, 0.0f);
    ngl::Vec3 from(0.0f, 2.0f, 2.0f);
    return ngl::lookAt(from, to, up);
}

CameraComponents::CameraComponents(size_t i_size) {

    glClearColor(0.4f, 0.4f, 0.4f, 1.0f); // Grey Background
    glEnable(GL_DEPTH_TEST);
    constexpr auto vertexShader = "PBRVertex";
    constexpr auto fragShader = "PBRFragment";
    constexpr auto PBR = "PBR";
    ngl::ShaderLib::createShaderProgram(PBR);
    ngl::ShaderLib::attachShader(vertexShader, ngl::ShaderType::VERTEX);
    ngl::ShaderLib::attachShader(fragShader, ngl::ShaderType::FRAGMENT);
    ngl::ShaderLib::loadShaderSource(vertexShader, "shaders/PBRVertex.glsl");
    ngl::ShaderLib::loadShaderSource(fragShader, "shaders/PBRFragment.glsl");
    ngl::ShaderLib::compileShader(vertexShader);
    ngl::ShaderLib::compileShader(fragShader);
    ngl::ShaderLib::attachShaderToProgram(PBR, vertexShader);
    ngl::ShaderLib::attachShaderToProgram(PBR, fragShader);
    ngl::ShaderLib::linkProgramObject(PBR);
    ngl::ShaderLib::use(PBR);
    ngl::Vec3 from(0.0f, 2.0f, 2.0f);

    glViewport(0, 0, 1080, 720);
    for (size_t i = 0; i < i_size; i++) {
        m_view.push_back(getDefaultView());
        m_proj.push_back(getDefaultProj());
    }    ngl::ShaderLib::setUniform("camPos", from);
    ngl::ShaderLib::setUniform("lightPosition", 0.0f, 2.0f, 2.0f);
    ngl::ShaderLib::setUniform("lightColor", 400.0f, 400.0f, 400.0f);
    ngl::ShaderLib::setUniform("exposure", 2.2f);
    ngl::ShaderLib::setUniform("albedo", 0.950f, 0.71f, 0.29f);

    ngl::ShaderLib::setUniform("metallic", 1.02f);
    ngl::ShaderLib::setUniform("roughness", 0.38f);
    ngl::ShaderLib::setUniform("ao", 0.2f);
    ngl::VAOPrimitives::createTrianglePlane("floor", 20, 20, 1, 1, ngl::Vec3::up());

    ngl::ShaderLib::use(ngl::nglCheckerShader);
    ngl::ShaderLib::setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
    ngl::ShaderLib::setUniform("checkOn", true);
    ngl::ShaderLib::setUniform("lightPos", 0.0f, 2.0f, 2.0f);
    ngl::ShaderLib::setUniform("colour1", 0.9f, 0.9f, 0.9f, 1.0f);
    ngl::ShaderLib::setUniform("colour2", 0.6f, 0.6f, 0.6f, 1.0f);
    ngl::ShaderLib::setUniform("checkSize", 60.0f);
}
