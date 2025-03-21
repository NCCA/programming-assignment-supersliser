//
// Created by s5605187 on 20/03/25.
//

#include "PlaceableItem.h"

void PlaceableItem::use()
{
    // Placeholder
}

PlaceableItem PlaceableItem::createItem(const int i_id)
{
    switch (i_id)
    {
    case 1:
        return Grass();
    case 2:
        return Log();
    case 3:
        return Leaves();
    case 4:
        return Stone();
    case 5:
        return Planks();
        case 0:
        default:
            return PlaceableItem("NUll_ITEM", 0);
    }
}