//
// Created by s5605187 on 20/03/25.
//

#include "UseableItem.h"

void UseableItem::use()
{
    // Placeholder
}

UseableItem UseableItem::createItem(e_item i_item)
{
    UseableItem item;
    item.m_item = static_cast<e_item>(i_item);
    return item;
}

e_item UseableItem::item() const
{
    return m_item;
}