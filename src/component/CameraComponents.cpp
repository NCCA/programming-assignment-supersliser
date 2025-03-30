//
// Created by thoma on 24/03/2025.
//

#include "component/CameraComponents.h"
#include "dir.h"


CameraComponents::CameraComponents(size_t i_size) {
    ngl::NGLInit::initialize();
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f); // Grey Background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    constexpr auto vertexShader = "SimpleVertex";
    constexpr auto fragShader = "SimpleFragment";

    ngl::ShaderLib::createShaderProgram("TextureShader");

    ngl::ShaderLib::debugOn();

    ngl::ShaderLib::attachShader(vertexShader, ngl::ShaderType::VERTEX);
    ngl::ShaderLib::attachShader(fragShader, ngl::ShaderType::FRAGMENT);

    ngl::ShaderLib::loadShaderSource(vertexShader,  fmt::format("{}{}", DIR, "shaders/TextureVert.glsl"));
    ngl::ShaderLib::loadShaderSource(fragShader, fmt::format("{}{}", DIR, "shaders/TextureFrag.glsl"));
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
        auto camera = Camera();
        camera.setDefaultCamera();
        m_cameras.push_back(camera);
    }

    ngl::ShaderLib::debugOff();
}
