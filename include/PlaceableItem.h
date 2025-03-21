//
// Created by s5605187 on 20/03/25.
//

#ifndef PLACEABLEITEM_H
#define PLACEABLEITEM_H
#include "Item.h"
#include "PlacedEntity.h"

class PlaceableItem : public a_Item
{
protected:
    PlacedEntity m_placedItem;
public:
    void use() override;
    static PlaceableItem createItem(const int i_id);
    PlaceableItem() = default;
    PlaceableItem(const std::string& i_name, const unsigned int i_id): a_Item(i_name, i_id) {}
    ~PlaceableItem() override = default;
};

class Grass : public PlaceableItem
{
public:
    Grass() : PlaceableItem("GRASS", 1) {}
    void use() override;
};

class Log : public PlaceableItem
{
public:
    Log() : PlaceableItem("LOG", 2) {}
    void use() override;
};

class Leaves : public PlaceableItem
{
public:
    Leaves() : PlaceableItem("LEAVES", 3) {}
    void use() override;
};

class Stone : public PlaceableItem
{
public:
    Stone() : PlaceableItem("STONE", 4) {}
    void use() override;
};

class Planks : public PlaceableItem
{
public:
    Planks() : PlaceableItem("PLANKS", 5) {}
    void use() override;
};

#endif //PLACEABLEITEM_H
