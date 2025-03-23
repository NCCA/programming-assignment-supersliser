//
// Created by thoma on 23/03/2025.
//

#include "component/BlockComponent.h"

BlockComponent::BlockComponent(size_t i_size) {
    for (size_t i = 0; i < i_size; i++) {
        m_textures.push_back(ngl::Texture(Texture));
    }
}