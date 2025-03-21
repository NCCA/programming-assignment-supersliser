//
// Created by s5605187 on 21/03/25.
//

#ifndef FILLABLEINVENTORY_H
#define FILLABLEINVENTORY_H
#include "Inventory.h"

class FillableInventory : public Inventory
{
protected:
    int m_maxItems;

public:
    void addItem(a_Item i_item, int i_quantity) override;
    FillableInventory() = default;
    FillableInventory(int i_maxItems);
    virtual ~FillableInventory() = default;
};

#endif //FILLABLEINVENTORY_H
