#version 420 core
// this is a pointer to the current 2D texture object
uniform sampler2D tex;
// the vertex UV
in vec2 vertUV;
// the final fragment colour
layout (location =0) out vec4 outColour;
uniform mat4 MVP;
// Normal matrix for transforming normals
uniform mat3 normalMatrix;

void main ()
{
 // set the fragment colour to the current texture
 outColour = texture(tex,vertUV);
}
