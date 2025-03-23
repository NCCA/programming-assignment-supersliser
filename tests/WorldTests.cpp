//
// Created by thoma on 23/03/2025.
//
#include "system/MoveSystem.h"
#include <gtest/gtest.h>
#include "Table.h"
#include "system/SetPositionSystem.h"

TEST(System, generateWorld)
{
    Table world;
    for (uint32_t i = 0; i < 9; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(TransformComponent::getComponentID());
    SetPositionSystem setPositionSystem;
    for (float i = -1; i <= 1; i++)
    {
        for (float j = -1; j <= 1; j++)
        {
            setPositionSystem.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&setPositionSystem, TransformComponent::getComponentID(),  (i + 1) * 3 + (j + 1), (i + 1) * 3 + (j + 1));
        }
    }
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(0)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[0]==ngl::Vec3(-1.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(1)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[1]==ngl::Vec3(-1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(2)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[2]==ngl::Vec3(-1.0f, 0.0f, 1.0f));
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(3)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[3]==ngl::Vec3(0.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(4)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[4]==ngl::Vec3(0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(5)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[5]==ngl::Vec3(0.0f, 0.0f, 1.0f));
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(6)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[6]==ngl::Vec3(1.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(7)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[7]==ngl::Vec3(1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponent*>(world.getEntity(8)[world.getComponentIndex(TransformComponent::getComponentID())].m_column)->m_ps[8]==ngl::Vec3(1.0f, 0.0f, 1.0f));
}

TEST(System, moveEntityInWorld)
{
    Table world;
    for (uint32_t i = 0; i < 12; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(TransformComponent::getComponentID());
    SetPositionSystem setPositionSystem;
    for (float i = -1; i <= 1; i++)
    {
        for (float j = -1; j <= 1; j++)
        {

            std::vector<float> args;
            setPositionSystem.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&setPositionSystem, TransformComponent::getComponentID(), (i + 1) * 3 + (j + 1), (i + 1) * 3 + (j + 1));
        }
    }
    setPositionSystem.i_pos = ngl::Vec3(1.0f, 1.0f, 0.0f);
    world.run(&setPositionSystem, TransformComponent::getComponentID(), 9, 9);
    setPositionSystem.i_pos = ngl::Vec3(-1.0f, 1.0f, 1.0f);
    world.run(&setPositionSystem, TransformComponent::getComponentID(), 10, 10);
    setPositionSystem.i_pos = ngl::Vec3(0.0f, 1.0f, 1.0f);
    world.run(&setPositionSystem, TransformComponent::getComponentID(), 11, 11);

    MoveSystem m;
    Table character;
    character.createEntity();
    character.registerComponentType(TransformComponent::getComponentID());
    setPositionSystem.i_pos = ngl::Vec3(0.0f, 1.0f, 0.0f);
    character.run(&setPositionSystem, TransformComponent::getComponentID());
    m.i_pos = ngl::Vec3(1.0f, 0.0f, 0.0f);
    m.i_world = &world;
    character.run(&m, TransformComponent::getComponentID());
    EXPECT_TRUE(static_cast<TransformComponent*>(character.getEntity(0)[1].m_column)->m_ps[0] == ngl::Vec3(0.0f, 1.0f, 0.0f));
    m.i_pos = ngl::Vec3(0.0f, 0.0f, -1.0f);
    m.i_world = &world;
    character.run(&m, TransformComponent::getComponentID());
    EXPECT_TRUE(static_cast<TransformComponent*>(character.getEntity(0)[1].m_column)->m_ps[0] == ngl::Vec3(0.0f, 1.0f, -1.0f));

}