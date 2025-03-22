//
// Created by s5605187 on 22/03/25.
//

#include "MoveSystem.h"
#include <gtest/gtest.h>
#include "Table.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Table, AddEntity) {
    Table table;
    uint32_t entity = table.createEntity();
    EXPECT_EQ(entity, 0);
    uint32_t entity2 = table.createEntity();
    EXPECT_EQ(entity2, 1);
}

TEST(Table, AddComponent) {
    Table table;
    uint32_t entity = table.createEntity();
    table.registerComponentType(PositonComponent().getComponentID());
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    table.registerComponentType(PositonComponent().getComponentID());
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    uint32_t entity2 = table.createEntity();
    EXPECT_EQ(table.getEntity(entity2).size(), 2);
}

TEST(System, RunSystem) {
    Table table;
    uint32_t entity = table.createEntity();
    table.registerComponentType(PositonComponent().getComponentID());
    for (uint32_t i = 1; i < 10; i++) {
        uint32_t entity2 = table.createEntity();

    }
    MoveSystem moveSystem;
    table.run(moveSystem, 2);
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        PositonComponent* positionComponent = static_cast<PositonComponent*>(entity3[1].m_column);
        EXPECT_EQ(positionComponent->m_ps[i].m_x, 1);
    }
}