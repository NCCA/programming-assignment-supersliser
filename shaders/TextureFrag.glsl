#version 420 core
// this is a pointer to the current 2D texture object
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D tex5;
uniform sampler2D tex6;
uniform sampler2D tex7;
// the vertex UV
in vec2 vertUV;
in flat uint TexID;
// the final fragment colour
layout (location =0) out vec4 outColour;
uniform mat4 MVP;
// Normal matrix for transforming normals
uniform mat3 normalMatrix;

void main ()
{
 // set the fragment colour to the current texture
 switch (TexID) {
    case 0:
     outColour = texture(tex1,vertUV);
    break;
    case 1:
     outColour = texture(tex2,vertUV);
    break;
    case 2:
     outColour = texture(tex3,vertUV);
    break;
    case 3:
     outColour = texture(tex4,vertUV);
    break;
    case 4:
     outColour = texture(tex5,vertUV);
    break;
    case 5:
     outColour = texture(tex6,vertUV);
    break;
    case 6:
     outColour = texture(tex7,vertUV);
    break;
    default:
     outColour = texture(tex1,vertUV);
 }
}
