#version 420 core

/// @brief MVP passed from app
uniform mat4 MVP;
// first attribute the vertex values from our VAO
layout (location=0) in vec3 inVert;
// second attribute the UV values from our VAO
layout (location=1)in vec2 inUV;
// third attribute the position values from our VAO
layout (location=2)in vec3 inLoc;
// fourth attribute the texture ID from our VAO
layout (location=3)in float inTexID;
// we use this to pass the UV values to the frag shader
out vec2 vertUV;
// we use this to pass the texture ID to the frag shader
out float TexID;


void main()
{
// pre-calculate for speed we will use this a lot
// calculate the vertex position
gl_Position = MVP*vec4(inVert + inLoc, 1.0);
// pass the UV values to the frag shader
vertUV=inUV;
TexID=inTexID;
}
