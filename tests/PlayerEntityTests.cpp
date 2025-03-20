//
// Created by tom on 3/20/25.
//
#include <gtest//gtest.h>
#include "PlayerEntity.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PlayerEntity, DefaultConstructor)
{
    PlayerEntity player;
    EXPECT_EQ(player.position(), ngl::Vec3(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(player.direction(), ngl::Vec3(0.0f, 0.0f, 1.0f));
    EXPECT_EQ(player.health(), 100);
    EXPECT_EQ(player.speed(), 1);
    EXPECT_EQ(player.visible(), true);
    EXPECT_EQ(player.selected(), false);
}

TEST(PlayerEntity, Constructor)
{
    PlayerEntity player = PlayerEntity(ngl::Vec3(1.0f, 2.0f, 3.0f), ngl::Vec3(0.0f, 0.0f, 1.0f), 50);
    EXPECT_EQ(player.position(), ngl::Vec3(1.0f, 2.0f, 3.0f));
    EXPECT_EQ(player.direction(), ngl::Vec3(0.0f, 0.0f, 1.0f));
    EXPECT_EQ(player.health(), 50);
    EXPECT_EQ(player.speed(), 1);
    EXPECT_EQ(player.visible(), true);
    EXPECT_EQ(player.selected(), false);
}

TEST(PlayerEntity, WalkForwards)
{
    PlayerEntity player;

    const ngl::Vec2 direction = ngl::Vec2(0.0f, 1.0f);
    const ngl::Vec3 EXPECTED_OUTPUT = ngl::Vec3(0.0f, 0.0f, 1.0f);

    player.setDirection(ngl::Vec3(0.0f, 0.0f, 1.0f));
    player.move(direction);


    EXPECT_FLOAT_EQ(player.position().m_x, EXPECTED_OUTPUT.m_x);
    EXPECT_FLOAT_EQ(player.position().m_y, EXPECTED_OUTPUT.m_y);
    EXPECT_FLOAT_EQ(player.position().m_z, EXPECTED_OUTPUT.m_z);
}

TEST(PlayerEntity, SprintForwards)
{
    PlayerEntity player;

    const ngl::Vec2 direction = ngl::Vec2(0.0f, 1.0f);
    const ngl::Vec3 EXPECTED_OUTPUT = ngl::Vec3(0.0f, 0.0f, 2.0f);

    player.setDirection(ngl::Vec3(0.0f, 0.0f, 1.0f));
    player.startSprint();
    player.move(direction);

    EXPECT_FLOAT_EQ(player.position().m_x, EXPECTED_OUTPUT.m_x);
    EXPECT_FLOAT_EQ(player.position().m_y, EXPECTED_OUTPUT.m_y);
    EXPECT_FLOAT_EQ(player.position().m_z, EXPECTED_OUTPUT.m_z);

    player.stopSprint();
    player.move(direction);

    const ngl::Vec3 EXPECTED_OUTPUT2 = ngl::Vec3(0.0f, 0.0f, 3.0f);

    EXPECT_FLOAT_EQ(player.position().m_x, EXPECTED_OUTPUT2.m_x);
    EXPECT_FLOAT_EQ(player.position().m_y, EXPECTED_OUTPUT2.m_y);
    EXPECT_FLOAT_EQ(player.position().m_z, EXPECTED_OUTPUT2.m_z);
}

TEST(PlayerEntity, SetRotation)
{
    PlayerEntity player;

    const ngl::Vec3 EXPECTED_OUTPUT = ngl::Vec3(0.0f, 1.0f, 0.0f);

    player.setDirection(EXPECTED_OUTPUT);

    EXPECT_FLOAT_EQ(player.direction().m_x, EXPECTED_OUTPUT.m_x);
    EXPECT_FLOAT_EQ(player.direction().m_y, EXPECTED_OUTPUT.m_y);
    EXPECT_FLOAT_EQ(player.direction().m_z, EXPECTED_OUTPUT.m_z);
}

TEST(PlayerEntity, Rotate)
{
    PlayerEntity player;

    const auto startDirection = ngl::Vec3(0.0f, 0.0f, 1.0f);
    const auto rotationAxis = ngl::Vec3(0.0f, 1.0f, 0.0f);
    const int rotationAmount = 90;
    auto EXPECTED_OUTPUT = ngl::Vec3(1.0f, 0.0f, 0.0f);

    player.setDirection(startDirection);
    player.rotate(rotationAxis, rotationAmount);

    EXPECT_TRUE(FCompare(player.direction().m_x, EXPECTED_OUTPUT.m_x));
    EXPECT_TRUE(FCompare(player.direction().m_y, EXPECTED_OUTPUT.m_y));
    EXPECT_TRUE(FCompare(player.direction().m_z, EXPECTED_OUTPUT.m_z));
}