//
// Created by s5605187 on 22/03/25.
//

#include "system/MoveSystem.h"
#include <gtest/gtest.h>
#include "Table.h"
#include "system/SetPositionSystem.h"

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
    table.registerComponentType(TransformComponent::getComponentID());
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    table.registerComponentType(TransformComponent::getComponentID());
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    uint32_t entity2 = table.createEntity();
    EXPECT_EQ(table.getEntity(entity2).size(), 2);
}

TEST(System, RunSystem) {
    Table table;
    for (uint32_t i = 0; i < 10; i++) {
        table.createEntity();
    }
    table.registerComponentType(TransformComponent::getComponentID());
    MoveSystem moveSystem;

    moveSystem.i_pos = ngl::Vec3{1.0f, 0.0f, 0.0f};
    table.run(&moveSystem, 2);
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        auto* positionComponent = static_cast<TransformComponent*>(entity3[table.getComponentIndex(TransformComponent::getComponentID())].m_column);
        EXPECT_EQ(positionComponent->m_ps[i].m_x, 1);
    }

    for (uint32_t i = 0; i < 10; i++)
    {
        table.createEntity();
    }
    table.run(&moveSystem, TransformComponent::getComponentID());
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        int index = table.getComponentIndex(TransformComponent::getComponentID());
        TransformComponent* positionComponent = static_cast<TransformComponent*>(entity3[index].m_column);
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 2.0f);
    }
    for (uint32_t i = 10; i < 20; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        TransformComponent* positionComponent = static_cast<TransformComponent*>(entity3[table.getComponentIndex(TransformComponent::getComponentID())].m_column);
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 1.0f);
    }
    table.run(&moveSystem, TransformComponent::getComponentID(), 10, 20);
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        int index = table.getComponentIndex(TransformComponent::getComponentID());
        TransformComponent* positionComponent = static_cast<TransformComponent*>(entity3[index].m_column);
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 2.0f);
    }
    for (uint32_t i = 10; i < 20; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        TransformComponent* positionComponent = static_cast<TransformComponent*>(entity3[table.getComponentIndex(TransformComponent::getComponentID())].m_column);
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 2.0f);
    }
}