//
// Created by s5605187 on 21/03/25.
//

#ifndef HOTBAR_H
#define HOTBAR_H

#include "FillableInventory.h"

class Hotbar : public FillableInventory
{
public:
    void selectItem(int i_index) override;
    void nextItem();
    void previousItem();
    Hotbar() : FillableInventory(9) {}
    ~Hotbar() override = default;
};

#endif //HOTBAR_H
