//
// Created by s5605187 on 20/03/25.
//

#ifndef USEABLEITEM_H
#define USEABLEITEM_H
#include "Item.h"

class UseableItem : public a_Item
{
public:
    void use() override;
    static UseableItem createItem(e_item i_item);
    e_item item() const;
};

#endif //USEABLEITEM_H
