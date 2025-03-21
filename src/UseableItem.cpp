//
// Created by s5605187 on 20/03/25.
//

#include "UseableItem.h"

void UseableItem::use()
{
    // Placeholder
}

UseableItem UseableItem::createItem(const int i_id)
{
    switch (i_id)
    {
        case 6:
            return Bow();
        case 7:
            return Arrow();
        default:
            return UseableItem("NULL_ITEM", 0);
    }
}