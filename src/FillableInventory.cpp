//
// Created by s5605187 on 21/03/25.
//


#include "FillableInventory.h"

FillableInventory::FillableInventory(int i_maxItems)
{
    m_maxItems = i_maxItems;
}

void FillableInventory::addItem(a_Item i_item, int i_quantity)
{
    if (m_slots.size() < m_maxItems)
    {
        Inventory::addItem(i_item, i_quantity);
    }
}