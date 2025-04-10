#version 420 core

// this is a pointer to the current 2D texture object

// the vertex UV
in vec2 vertUV;
in flat uint TexID;
// the final fragment colour
layout (location =0) out vec4 outColour;
uniform mat4 MVP;
uniform sampler2D tex[7];
// Normal matrix for transforming normals
uniform mat3 normalMatrix;

void main ()
{
//    outColour = vec4(TexID / 7, 0.0, 0.0, 1.0);
//  set the fragment colour to the current texture
// switch (TexID) {
//    case 0:
//     outColour = texture(texA,vertUV);
//    break;
//    case 1:
//     outColour = texture(texB,vertUV);
//    break;
//    case 2:
//     outColour = texture(texC,vertUV);
//    break;
//    case 3:
//     outColour = texture(texD,vertUV);
//    break;
//    case 4:
//     outColour = texture(texE,vertUV);
//    break;
//    case 5:
//     outColour = texture(texF,vertUV);
//    break;
//    case 6:
//     outColour = texture(texG,vertUV);
//    break;
////    default:
////     outColour = texture(texA,vertUV);
// }
    outColour = texture(tex[TexID],vertUV);
}
