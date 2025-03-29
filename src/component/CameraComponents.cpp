//
// Created by thoma on 24/03/2025.
//

#include "component/CameraComponents.h"

#include <ngl/NGLInit.h>
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
    ngl::NGLInit::initialize();
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f); // Grey Background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    constexpr auto vertexShader = "SimpleVertex";
    constexpr auto fragShader = "SimpleFragment";

    ngl::ShaderLib::createShaderProgram("TextureShader");

    ngl::ShaderLib::attachShader(vertexShader, ngl::ShaderType::VERTEX);
    ngl::ShaderLib::attachShader(fragShader, ngl::ShaderType::FRAGMENT);
    std::string path;
#ifdef __amd64__
    path = "/home/tom/programming-assignment-supersliser/";
#elif __linux__
    path = "/home/s5605187/Documents/programming-assignment-supersliser/";
#endif


    ngl::ShaderLib::loadShaderSource(vertexShader, path + "shaders/TextureVert.glsl");
    ngl::ShaderLib::loadShaderSource(fragShader, path + "shaders/TextureFrag.glsl");
    if (!ngl::ShaderLib::compileShader(vertexShader)) {
        std::cerr << "Vertex shader compilation failed\n";
        return;
    }
    if (!ngl::ShaderLib::compileShader(fragShader)) {
        std::cerr << "Fragment shader compilation failed\n";
        return;
    }
    ngl::ShaderLib::attachShaderToProgram("TextureShader", vertexShader);
    ngl::ShaderLib::attachShaderToProgram("TextureShader", fragShader);

    if (!ngl::ShaderLib::linkProgramObject("TextureShader")) {
        std::cerr << "Shader program linking failed\n";
        return;
    }
    ngl::ShaderLib::use("TextureShader");
    ngl::ShaderLib::setUniform("tex", 0);

    glViewport(0, 0, 1080, 720);
    for (size_t i = 0; i < i_size; i++) {
        m_view.push_back(getDefaultView());
        m_proj.push_back(getDefaultProj());
    }
}
