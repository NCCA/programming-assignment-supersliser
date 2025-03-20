//
// Created by s5605187 on 20/03/25.
//

#ifndef PLACEABLEITEM_H
#define PLACEABLEITEM_H
#include "Item.h"

class PlaceableItem : public a_Item
{
public:
    void use() override;
    static PlaceableItem createItem(e_item i_item);
    e_item item() const;
};

#endif //PLACEABLEITEM_H
