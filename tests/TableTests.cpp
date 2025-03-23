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
    table.registerComponentType(PositonComponent::getComponentID());
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    table.registerComponentType(PositonComponent::getComponentID());
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    uint32_t entity2 = table.createEntity();
    EXPECT_EQ(table.getEntity(entity2).size(), 2);
}

TEST(System, RunSystem) {
    Table table;
    for (uint32_t i = 0; i < 10; i++) {
        table.createEntity();
    }
    table.registerComponentType(PositonComponent::getComponentID());
    MoveSystem moveSystem;
    std::vector<float> args;
    args.push_back(1);
    args.push_back(0);
    args.push_back(0);

    table.run(&moveSystem, 2, args);
    table.run(&moveSystem, 3, args);
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        auto* positionComponent = static_cast<PositonComponent*>(entity3[table.getComponentIndex(PositonComponent::getComponentID())].m_column);
        EXPECT_EQ(positionComponent->m_ps[i].m_x, 1);
    }

    for (uint32_t i = 0; i < 10; i++)
    {
        table.createEntity();
    }
    table.run(&moveSystem, PositonComponent::getComponentID(), args);
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        int index = table.getComponentIndex(PositonComponent::getComponentID());
        PositonComponent* positionComponent = static_cast<PositonComponent*>(entity3[index].m_column);
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 2.0f);
    }
    for (uint32_t i = 10; i < 20; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        PositonComponent* positionComponent = static_cast<PositonComponent*>(entity3[table.getComponentIndex(PositonComponent::getComponentID())].m_column);
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 1.0f);
    }
    table.run(&moveSystem, PositonComponent::getComponentID(), args, nullptr, 10, 20);
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        int index = table.getComponentIndex(PositonComponent::getComponentID());
        PositonComponent* positionComponent = static_cast<PositonComponent*>(entity3[index].m_column);
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 2.0f);
    }
    for (uint32_t i = 10; i < 20; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        PositonComponent* positionComponent = static_cast<PositonComponent*>(entity3[table.getComponentIndex(PositonComponent::getComponentID())].m_column);
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 2.0f);
    }
}

TEST(System, generateWorld)
{
    Table world;
    for (uint32_t i = 0; i < 9; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(PositonComponent::getComponentID());
    SetPositionSystem setPositionSystem;
    for (float i = -1; i <= 1; i++)
    {
        for (float j = -1; j <= 1; j++)
        {

            std::vector<float> args;
            args.push_back((i + 1) * 3 + (j + 1));
            args.push_back(i);
            args.push_back(0.0f);
            args.push_back(j);
            world.run(&setPositionSystem, PositonComponent::getComponentID(), args, 0, 0);
        }
    }
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(0)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[0]==ngl::Vec3(-1.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(1)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[1]==ngl::Vec3(-1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(2)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[2]==ngl::Vec3(-1.0f, 0.0f, 1.0f));
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(3)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[3]==ngl::Vec3(0.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(4)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[4]==ngl::Vec3(0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(5)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[5]==ngl::Vec3(0.0f, 0.0f, 1.0f));
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(6)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[6]==ngl::Vec3(1.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(7)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[7]==ngl::Vec3(1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<PositonComponent*>(world.getEntity(8)[world.getComponentIndex(PositonComponent::getComponentID())].m_column)->m_ps[8]==ngl::Vec3(1.0f, 0.0f, 1.0f));
}

TEST(System, moveEntityInWorld)
{
    Table world;
    for (uint32_t i = 0; i < 12; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(PositonComponent::getComponentID());
    SetPositionSystem setPositionSystem;
    for (float i = -1; i <= 1; i++)
    {
        for (float j = -1; j <= 1; j++)
        {

            std::vector<float> args;
            args.push_back((i + 1) * 3 + (j + 1));
            args.push_back(i);
            args.push_back(0.0f);
            args.push_back(j);
            world.run(&setPositionSystem, PositonComponent::getComponentID(), args, 0, 0);
        }
    }
    world.run(&setPositionSystem, PositonComponent::getComponentID(), {10.0f, 1.0f, 1.0f, 0.0f}, nullptr, 0, 0);
    world.run(&setPositionSystem, PositonComponent::getComponentID(), {11.0f, -1.0f, 1.0f, 0.0f}, nullptr, 0, 0);
    world.run(&setPositionSystem, PositonComponent::getComponentID(), {11.0f, 0.0f, 1.0f, 1.0f}, nullptr, 0, 0);

    MoveSystem m;
    Table character;
    character.createEntity();
    character.registerComponentType(PositonComponent::getComponentID());
    character.run(&setPositionSystem, PositonComponent::getComponentID(), {10.0f, 0.0f, 1.0f, 0.0f}, nullptr, 0, 0);
    character.run(&m, PositonComponent::getComponentID(), {1.0f, 0.0f, 0.0f}, &world);
    EXPECT_TRUE(static_cast<PositonComponent*>(character.getEntity(0)[1].m_column)->m_ps[0] == ngl::Vec3(0.0f, 1.0f, 0.0f));
    character.run(&m, PositonComponent::getComponentID(), {0.0f, 0.0f, -1.0f}, &world);
    EXPECT_TRUE(static_cast<PositonComponent*>(character.getEntity(0)[1].m_column)->m_ps[0] == ngl::Vec3(0.0f, 1.0f, -1.0f));

}