#version 420 core

// this is a pointer to the current 2D texture object

// the vertex UV
in vec2 vertUV;
in float TexID;
// the final fragment colour
layout (location =0) out vec4 outColour;
uniform mat4 MVP;
uniform sampler2D tex[7];
// Normal matrix for transforming normals
uniform mat3 normalMatrix;

void main ()
{
//    if (TexID == 0) {
//        outColour = vec4(1.0, 0.0, 0.0, 1.0);
//    }
//    else if (TexID == 1) {
//        outColour = vec4(0.0, 1.0, 0.0, 1.0);
//    }
//    else if (TexID == 2) {
//        outColour = vec4(0.0, 0.0, 1.0, 1.0);
//    }
//    else if (TexID == 3) {
//        outColour = vec4(1.0, 1.0, 0.0, 1.0);
//    }
//    else if (TexID == 4) {
//        outColour = vec4(1.0, 0.5, 0.5, 1.0);
//    }
//    else if (TexID == 5) {
//        outColour = vec4(0.5, 1.0, 1.0, 1.0);
//    }
//    else if (TexID == 6) {
//        outColour = vec4(1.0, 1.0, 1.0, 1.0);
//    }
//    else if (TexID == 7) {
//        outColour = vec4(0.0, 0.0, 0.0, 1.0);
//    }
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
    int texIndex = int(floor(TexID + 0.5)); // More reliable rounding

    if (texIndex < 0 || texIndex > 6) {
        outColour = texture(tex[0], vertUV);
        return;
    }

    outColour = texture(tex[texIndex], clamp(vertUV, 0.0, 1.0));
}
