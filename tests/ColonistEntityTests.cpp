//
// Created by s5605187 on 20/03/25.
//

#include <gtest/gtest.h>
#include "ColonistEntity.h"

TEST(ColonistEntity, DefaultConstructor)
{
    ColonistEntity colonist;
    EXPECT_EQ(colonist.position(), ngl::Vec3(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(colonist.direction(), ngl::Vec3(0.0f, 0.0f, 1.0f));
    EXPECT_EQ(colonist.health(), 100);
    EXPECT_EQ(colonist.speed(), 1);
    EXPECT_EQ(colonist.visible(), true);
    EXPECT_EQ(colonist.selected(), false);
    EXPECT_EQ(colonist.job(), e_job::UNEMPLOYED);
}

TEST(ColonistEntity, Constructor)
{
    ColonistEntity colonist = ColonistEntity(ngl::Vec3(1.0f, 2.0f, 3.0f), ngl::Vec3(0.0f, 0.0f, 1.0f), e_job::BAKER);
    EXPECT_EQ(colonist.position(), ngl::Vec3(1.0f, 2.0f, 3.0f));
    EXPECT_EQ(colonist.direction(), ngl::Vec3(0.0f, 0.0f, 1.0f));
    EXPECT_EQ(colonist.health(), 100);
    EXPECT_EQ(colonist.speed(), 1);
    EXPECT_EQ(colonist.visible(), true);
    EXPECT_EQ(colonist.selected(), false);
    EXPECT_EQ(colonist.job(), e_job::BAKER);
}

TEST(ColonistEntity, WalkForwards)
{
    ColonistEntity colonist;

    const ngl::Vec2 direction = ngl::Vec2(0.0f, 1.0f);
    const ngl::Vec3 EXPECTED_OUTPUT = ngl::Vec3(0.0f, 0.0f, 1.0f);

    colonist.move(direction);

    EXPECT_TRUE(FCompare(colonist.position().m_x, EXPECTED_OUTPUT.m_x));
    EXPECT_TRUE(FCompare(colonist.position().m_y, EXPECTED_OUTPUT.m_y));
    EXPECT_TRUE(FCompare(colonist.position().m_z, EXPECTED_OUTPUT.m_z));
}

TEST(ColonistEntity, WalkLeft)
{
    ColonistEntity colonist;

    const auto direction = ngl::Vec2(1.0f, 0.0f);
    const auto EXPECTED_OUTPUT = ngl::Vec3(1.0f, 0.0f, 0.0f);

    colonist.move(direction);

    EXPECT_TRUE(FCompare(colonist.position().m_x, EXPECTED_OUTPUT.m_x));
    EXPECT_TRUE(FCompare(colonist.position().m_y, EXPECTED_OUTPUT.m_y));
    EXPECT_TRUE(FCompare(colonist.position().m_z, EXPECTED_OUTPUT.m_z));
}