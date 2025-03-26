//
// Created by thoma on 24/03/2025.
//

#include "system/RenderCubeSystem.h"

#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>

#include "component/BlockComponents.h"

void RenderCubeSystem::run(BlockComponents* io_component, int i_index) {
    // vertex coords array
    GLfloat vertices[] = {
            -1, 1, -1, 1, 1, -1, 1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, // back
            -1, 1, 1, 1, 1, 1, 1, -1, 1, -1, -1, 1, 1, -1, 1, -1, 1, 1,       // front
            -1, 1, -1, 1, 1, -1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, -1,       // top
            -1, -1, -1, 1, -1, -1, 1, -1, 1, -1, -1, 1, 1, -1, 1, -1, -1, -1, // bottom
            -1, 1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, // left
            1, 1, -1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, -1, 1, 1, 1, 1,       // left

    };
    GLfloat texture[] = {
            0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, // back
            0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, // front
            0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, // top
            0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, // bottom
            1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, // left
            1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, // right

    };

    // first we scale our vertices to _scale
    for (uint i = 0; i < sizeof(vertices) / sizeof(GLfloat); ++i)
    {
        vertices[i] *= 0.2f;
    }
    GLuint vaoID;
// first we create a vertex array Object
    glGenVertexArrays(1, &vaoID);

    // now bind this to be the currently active one
    glBindVertexArray(vaoID);
    // now we create two VBO's one for each of the objects these are only used here
    // as they will be associated with the vertex array object
    GLuint vboID[2];
    glGenBuffers(2, &vboID[0]);
    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    // now we bind the vertex attribute pointer for this object in this case the
    // vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    // now we repeat for the UV data using the second VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture) * sizeof(GLfloat), texture, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    auto tx = ngl::Mat4::translate(i_pos.m_x, i_pos.m_y, i_pos.m_z);
    ngl::Mat4 MVP = m_camera->m_proj[0] * m_camera->m_view[0] * tx;
    ngl::Mat3 normalMatrix = m_camera->m_view[0];
    normalMatrix.inverse().transpose();
    ngl::ShaderLib::setUniform("MVP", MVP);

    ngl::ShaderLib::use("TextureShader");
    // now we bind back our vertex array object and draw
    glBindVertexArray(vaoID); // select first VAO

    int instances = 0;
    // need to bind the active texture before drawing
    glBindTexture(GL_TEXTURE_2D, m_texture->m_textures[i_index]);

    ngl::ShaderLib::setUniform("MVP", MVP);
    ngl::ShaderLib::setUniform("normalMatrix", normalMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36); // draw object
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}
