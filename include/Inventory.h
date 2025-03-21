//
// Created by s5605187 on 21/03/25.
//

#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>

#include "Slot.h"

class Inventory
{
protected:
    std::vector<Slot> m_slots;
    int m_selectedItemIndex;
    bool m_moving;
public:
    virtual void addItem(a_Item i_item, int i_quantity = 1);
    void removeItem(a_Item i_item, int i_quantity = 1);
    Slot getItem();
    void startMoveItem();
    void moveItem(Slot* i_slot);
    void stopMoveItem();
    virtual void selectItem(int i_index);
    Inventory() = default;
    ~Inventory() = default;
};
#endif //INVENTORY_H
