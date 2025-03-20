//
// Created by s5605187 on 20/03/25.
//

#include "PlaceableItem.h"

void PlaceableItem::use()
{
    // Placeholder
}

PlaceableItem PlaceableItem::createItem(e_item i_item)
{
    PlaceableItem item;
    item.m_item = static_cast<e_item>(i_item);
    return item;
}

e_item PlaceableItem::item() const
{
    return m_item;
}