#version 420 core

// this is a pointer to the current 2D texture object

// the vertex UV
in vec2 vertUV;
// the texture ID
in float TexID;
// the final fragment colour
layout (location = 0) out vec4 outColour;
// the vertex position
uniform mat4 MVP;
// the texture samplers
uniform sampler2D tex[7];
// Normal matrix for transforming normals
uniform mat3 normalMatrix;

void main ()
{
    int texIndex = int(floor(TexID + 0.5)); // More reliable rounding

    if (texIndex < 0 || texIndex > 6) {
        outColour = texture(tex[0], vertUV);
        return;
    }

    outColour = texture(tex[texIndex], clamp(vertUV, 0.0, 1.0));
}
