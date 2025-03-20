//
// Created by s5605187 on 20/03/25.
//

#include <gtest/gtest.h>

#include "PlaceableItem.h"
#include "UseableItem.h"
TEST(PlaceableItem, Constructors)
{
    PlaceableItem i;
    i = PlaceableItem::createItem(static_cast<e_item>(e_item::LOG));
    EXPECT_EQ(i.item(), e_item::LOG);
    i = PlaceableItem::createItem(static_cast<e_item>(e_item::GRASS));
    EXPECT_EQ(i.item(), e_item::GRASS);
    i = PlaceableItem::createItem(static_cast<e_item>(e_item::STONE));
    EXPECT_EQ(i.item(), e_item::STONE);
    i = PlaceableItem::createItem(static_cast<e_item>(e_item::LEAVES));
    EXPECT_EQ(i.item(), e_item::LEAVES);
    i = PlaceableItem::createItem(static_cast<e_item>(e_item::PLANKS));
    EXPECT_EQ(i.item(), e_item::PLANKS);
}

TEST(UseableItem, Constructors)
{
    UseableItem i;
    i = UseableItem::createItem(static_cast<e_item>(e_item::BOW));
    EXPECT_EQ(i.item(), e_item::BOW);
    i = UseableItem::createItem(static_cast<e_item>(e_item::ARROW));
    EXPECT_EQ(i.item(), e_item::ARROW);
}