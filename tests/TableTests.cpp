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
    table.addComponent(new TransformComponent(), entity);
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    table.addComponent(new TransformComponent(), entity);
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    uint32_t entity2 = table.createEntity();
    table.addComponent(new TransformComponent(), entity2);
    EXPECT_EQ(table.getEntity(entity2).size(), 2);
}

TEST(System, RunSystem) {
    Table table;
    for (uint32_t i = 1; i < 10; i++) {
        uint32_t entity = table.createEntity();
        table.addComponent(new TransformComponent(), entity);
    }
    MoveSystem moveSystem;
    table.run(moveSystem, 2);
    for (uint32_t i = 0; i < 10; i++) {
        auto entity = table.getEntity(i);
        auto transform = dynamic_cast<TransformComponent*>(entity[1]);
        EXPECT_EQ(transform->m_p.m_x, 1);
    }
}