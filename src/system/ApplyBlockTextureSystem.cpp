//
// Created by s5605187 on 26/03/25.
//

#include "system/ApplyBlockTextureSystem.h"

void ApplyBlockTextureSystem::run(BlockTextureComponent* io_component, int i_index)
{
    ngl::Image image;
    bool loaded = image.load("/home/tom/programming-assignment-supersliser/textures/crate.bmp");
    if (loaded == true)
    {
        int width = image.width();
        int height = image.height();

        std::unique_ptr<unsigned char[]> data = std::make_unique<unsigned char[]>(width * height * 3);
        size_t index = 0;
        ngl::Vec3 colour;
        for (unsigned int y = 0; y < height; ++y)
        {
            for (unsigned int x = 0; x < width; ++x)
            {
                colour = image.getColour(x, y);

                data[index++] = colour.m_r;
                data[index++] = colour.m_g;
                data[index++] = colour.m_b;
            }
        }

        GLuint textureName;


        glGenTextures(1, &textureName);
        glBindTexture(GL_TEXTURE_2D, textureName);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        io_component->m_textures[i_index] = textureName;


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.get());

        glGenerateMipmap(GL_TEXTURE_2D); //  Allocate the mipmaps
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}