//
// Created by s5605187 on 21/03/25.
//

#ifndef SLOT_H
#define SLOT_H
#include "Item.h"

class Slot
{
protected:
    a_Item m_item;
    int m_quantity = 0;
    int m_maxItems = 64;
public:
    void setItem(a_Item i_item);
    a_Item item();
    void setQuantity(int i_quantity);
    void add(int i_quantity);
    void remove(int i_quantity);
    int quantity();
    Slot() = default;
    Slot(const a_Item i_item, const int i_quantity = 1,const int i_maxItems = 64);
    ~Slot();
};

#endif //SLOT_H
