//
// Created by s5605187 on 20/03/25.
//

#include "Item.h"

void a_Item::use()
{
    // Do nothing
}

std::string a_Item::name()
{
    return m_name;
}

a_Item::a_Item(const std::string& i_name, const unsigned int i_id)
{
    m_name = i_name;
    m_id = i_id;
}