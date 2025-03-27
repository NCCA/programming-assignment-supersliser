//
// Created by thoma on 23/03/2025.
//

#ifndef BLOCKCOMPONENT_H
#define BLOCKCOMPONENT_H

#include <ngl/Texture.h>

class BlockComponents
{
public:
    BlockComponents(size_t i_size);
    static std::uint8_t getComponentID() { return 3; }

    static std::array<ngl::Vec2, 36> getTexCoordinates() {
        std::array<ngl::Vec2, 36> texCoords;
        size_t i = 0;

        // Define texture coordinates for each vertex of each triangle

        // Front face
        texCoords[i++] = ngl::Vec2(0.0f, 0.0f); // v0
        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v1
        texCoords[i++] = ngl::Vec2(1.0f, 1.0f); // v2

        texCoords[i++] = ngl::Vec2(1.0f, 1.0f); // v2
        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v3
        texCoords[i++] = ngl::Vec2(0.0f, 0.0f); // v0

        // Back face
        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v5
        texCoords[i++] = ngl::Vec2(0.0f, 0.0f); // v4
        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v7

        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v7
        texCoords[i++] = ngl::Vec2(1.0f, 1.0f); // v6
        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v5

        // Top face
        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v3
        texCoords[i++] = ngl::Vec2(1.0f, 1.0f); // v2
        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v6

        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v6
        texCoords[i++] = ngl::Vec2(0.0f, 0.0f); // v7
        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v3

        // Bottom face
        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v4
        texCoords[i++] = ngl::Vec2(1.0f, 1.0f); // v5
        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v1

        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v1
        texCoords[i++] = ngl::Vec2(0.0f, 0.0f); // v0
        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v4

        // Right face
        texCoords[i++] = ngl::Vec2(0.0f, 0.0f); // v1
        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v5
        texCoords[i++] = ngl::Vec2(1.0f, 1.0f); // v6

        texCoords[i++] = ngl::Vec2(1.0f, 1.0f); // v6
        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v2
        texCoords[i++] = ngl::Vec2(0.0f, 0.0f); // v1

        // Left face
        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v4
        texCoords[i++] = ngl::Vec2(0.0f, 0.0f); // v0
        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v3

        texCoords[i++] = ngl::Vec2(0.0f, 1.0f); // v3
        texCoords[i++] = ngl::Vec2(1.0f, 1.0f); // v7
        texCoords[i++] = ngl::Vec2(1.0f, 0.0f); // v4

        return texCoords;
    }

    // vertex data from google gemini
    static std::array<ngl::Vec3,36> getVertices() {
        std::array<ngl::Vec3, 36> vertices;
        size_t i = 0;

        // Define the 8 corner vertices (for reference)
        ngl::Vec3 v0(-1.0f, -1.0f,  1.0f); // Front Bottom Left
        ngl::Vec3 v1( 1.0f, -1.0f,  1.0f); // Front Bottom Right
        ngl::Vec3 v2( 1.0f,  1.0f,  1.0f); // Front Top Right
        ngl::Vec3 v3(-1.0f,  1.0f,  1.0f); // Front Top Left
        ngl::Vec3 v4(-1.0f, -1.0f, -1.0f); // Back Bottom Left
        ngl::Vec3 v5( 1.0f, -1.0f, -1.0f); // Back Bottom Right
        ngl::Vec3 v6( 1.0f,  1.0f, -1.0f); // Back Top Right
        ngl::Vec3 v7(-1.0f,  1.0f, -1.0f); // Back Top Left

        // Front face (2 triangles)
        vertices[i++] = v0;
        vertices[i++] = v1;
        vertices[i++] = v2;

        vertices[i++] = v2;
        vertices[i++] = v3;
        vertices[i++] = v0;

        // Back face
        vertices[i++] = v5;
        vertices[i++] = v4;
        vertices[i++] = v7;

        vertices[i++] = v7;
        vertices[i++] = v6;
        vertices[i++] = v5;

        // Top face
        vertices[i++] = v3;
        vertices[i++] = v2;
        vertices[i++] = v6;

        vertices[i++] = v6;
        vertices[i++] = v7;
        vertices[i++] = v3;

        // Bottom face
        vertices[i++] = v4;
        vertices[i++] = v5;
        vertices[i++] = v1;

        vertices[i++] = v1;
        vertices[i++] = v0;
        vertices[i++] = v4;

        // Right face
        vertices[i++] = v1;
        vertices[i++] = v5;
        vertices[i++] = v6;

        vertices[i++] = v6;
        vertices[i++] = v2;
        vertices[i++] = v1;

        // Left face
        vertices[i++] = v4;
        vertices[i++] = v0;
        vertices[i++] = v3;

        vertices[i++] = v3;
        vertices[i++] = v7;
        vertices[i++] = v4;

        return vertices;
    }
};

#endif //BLOCKCOMPONENT_H
