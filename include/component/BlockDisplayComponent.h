//
// Created by thoma on 27/03/2025.
//

#ifndef BLOCKDISPLAYCOMPONENT_H
#define BLOCKDISPLAYCOMPONENT_H

#include <cstdio>
#include <cstdint>

class BlockDisplayComponent
{
    BlockDisplayComponent(size_t i_size);
    static std::uint8_t getComponentID() { return 6; }
};

#endif //BLOCKDISPLAYCOMPONENT_H
