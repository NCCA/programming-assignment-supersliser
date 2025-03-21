//
// Created by s5605187 on 21/03/25.
//

#include "Inventory.h"

void Inventory::addItem(a_Item i_item, int i_quantity)
{
    for (auto& slot : m_slots)
    {
        if (slot.item().name() == i_item.name())
        {
            slot.add(i_quantity);
            return;
        }
    }
    m_slots.push_back(Slot(i_item, i_quantity));
}

void Inventory::removeItem(a_Item i_item, int i_quantity)
{
    for (int i = 0; i < m_slots.size(); i++)
    {
        if (m_slots[i].item().name() == i_item.name())
        {
            m_slots[i].remove(i_quantity);
            if (m_slots[i].quantity() == 0)
            {
                m_slots.erase(m_slots.begin() + i);
            }
            return;
        }
    }
}

Slot Inventory::getItem()
{
    return m_slots[m_selectedItemIndex];
}

void Inventory::startMoveItem()
{
    m_moving = true;
}

void Inventory::moveItem(Slot* i_slot)
{
    if (m_moving)
    {
        i_slot->add(m_slots[m_selectedItemIndex].quantity());
        m_slots.erase(m_slots.begin() + m_selectedItemIndex);
        m_moving = false;
    }
}

void Inventory::stopMoveItem()
{
    m_moving = false;
}

void Inventory::selectItem(int i_index)
{
    m_selectedItemIndex = i_index;
}