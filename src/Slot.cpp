//
// Created by s5605187 on 21/03/25.
//

#include "Slot.h"

Slot::Slot(const a_Item i_item, const int i_quantity, const int i_maxItems)
{
    setItem(i_item);
    setQuantity(i_quantity);
    m_maxItems = i_maxItems;
}

void Slot::setItem(a_Item i_item)
{
    m_item = i_item;
}

a_Item Slot::item()
{
    return m_item;
}

void Slot::setQuantity(int i_quantity)
{
    m_quantity = i_quantity;
}

int Slot::quantity()
{
    return m_quantity;
}

void Slot::add(int i_quantity)
{
    m_quantity += i_quantity;
}

void Slot::remove(int i_quantity)
{
    m_quantity -= i_quantity;
}