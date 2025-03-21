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
    static UseableItem createItem(const int  i_id);
    UseableItem() = default;
    UseableItem(const std::string& i_name, const unsigned int i_id): a_Item(i_name, i_id) {}
    ~UseableItem() override = default;
};

class Bow : public UseableItem
{
public:
    Bow() : UseableItem("BOW", 6) {}
    void use() override;
};

class Arrow : public UseableItem
{
public:
    Arrow() : UseableItem("ARROW", 7) {}
    void use() override;
};

#endif //USEABLEITEM_H
