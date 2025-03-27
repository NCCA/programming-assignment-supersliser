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

    // vertex data from https://gist.github.com/OrangeTide/fbe703b80d143983361f
    static std::vector<float> getVertices() { return std::vector<float> {
        /* face 1 */
        1.0, -1.0, -1.0,
        -1.0, 1.0, -1.0,
        1.0, 1.0, -1.0,

        -1.0, 1.0, -1.0,
        1.0, -1.0, -1.0,
        -1.0, -1.0, -1.0,

        /* face 2 */
        -1.0, 1.0, 1.0,
        1.0, -1.0, 1.0,
        1.0, 1.0, 1.0,

        1.0, -1.0, 1.0,
        -1.0, 1.0, 1.0,
        -1.0, -1.0, 1.0,

        /* face 3 */
        -1.0, 1.0, -1.0,
        -1.0, 1.0, 1.0,
        1.0, 1.0, -1.0,

        -1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, -1.0,

        /* face 4 */
        -1.0, -1.0, 1.0,
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,

        1.0, -1.0, 1.0,
        -1.0, -1.0, 1.0,
        1.0, -1.0, -1.0,

        /* face 5 */
        1.0, 1.0, -1.0,
        1.0, 1.0, 1.0,
        1.0, -1.0, 1.0,

        1.0, 1.0, -1.0,
        1.0, -1.0, 1.0,
        1.0, -1.0, -1.0,

        /* face 6 */
        -1.0, 1.0, 1.0,
        -1.0, 1.0, -1.0,
        -1.0, -1.0, 1.0,

        -1.0, -1.0, 1.0,
        -1.0, 1.0, -1.0,
        -1.0, -1.0, -1.0,
    };};
};

#endif //BLOCKCOMPONENT_H
