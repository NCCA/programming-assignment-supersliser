//
// Created by thoma on 24/03/2025.
//

#include <ngl/VAOFactory.h>

#include "component/CameraComponents.h"
#include "dir.h"

CameraComponents::CameraComponents(size_t i_size)
{
    // Initialize the shaders
    ngl::NGLInit::initialize();
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    constexpr auto vertexShader = "TextureVertex";
    constexpr auto fragShader = "TextureFragment";
    constexpr auto program = "TextureShader";

    ngl::ShaderLib::createShaderProgram(program);

    ngl::ShaderLib::debugOn();

    ngl::ShaderLib::attachShader(vertexShader, ngl::ShaderType::VERTEX);
    ngl::ShaderLib::attachShader(fragShader, ngl::ShaderType::FRAGMENT);

    const auto vertexPath = fmt::format("{}{}", getDir(), "shaders/TextureVert.glsl");
    const auto fragPath = fmt::format("{}{}", getDir(), "shaders/TextureFrag.glsl");
    ngl::ShaderLib::loadShaderSource(vertexShader,  vertexPath);
    ngl::ShaderLib::loadShaderSource(fragShader, fragPath);
    if (!ngl::ShaderLib::compileShader(vertexShader))
    {
        std::cerr << "Vertex shader compilation failed\n";
        return;
    }
    if (!ngl::ShaderLib::compileShader(fragShader))
    {
        std::cerr << "Fragment shader compilation failed\n";
        return;
    }
    ngl::ShaderLib::attachShaderToProgram(program, vertexShader);
    ngl::ShaderLib::attachShaderToProgram(program, fragShader);

    if (!ngl::ShaderLib::linkProgramObject(program))
    {
        std::cerr << "Shader program linking failed\n";
        return;
    }
    ngl::ShaderLib::use(program);

    // Initialise the camera
    glViewport(0, 0, 1080, 720);
    for (size_t i = 0; i < i_size; i++)
    {
        auto camera = Camera();
        camera.setDefaultCamera();
        m_cameras.push_back(camera);
    }

    ngl::ShaderLib::debugOff();
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Error Creating camera component: " << error << std::endl;
    }
}

CameraComponents::~CameraComponents()
{
    ngl::ShaderLib::use("TextureShader");
    ngl::ShaderLib::reset();
}
