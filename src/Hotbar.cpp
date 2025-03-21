//
// Created by s5605187 on 21/03/25.
//

#include "Hotbar.h"

void Hotbar::selectItem(int i_index)
{
    if (i_index < 0 || i_index >= m_slots.size())
    {
        return;
    }
    m_selectedItemIndex = i_index;
}

void Hotbar::nextItem()
{
    m_selectedItemIndex++;
    if (m_selectedItemIndex >= m_slots.size())
    {
        m_selectedItemIndex = 0;
    }
}

void Hotbar::previousItem()
{
    m_selectedItemIndex--;
    if (m_selectedItemIndex < 0)
    {
        m_selectedItemIndex = m_slots.size() - 1;
    }
}