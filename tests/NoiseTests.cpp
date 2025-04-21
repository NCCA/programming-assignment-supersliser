//
// Created by s5605187 on 06/04/25.
//

#include <gtest/gtest.h>
#include <PerlinNoise.hpp>

/// @brief Tests the generation of 2D Perlin noise.
/// @detial Tests by checking the UV center of the generated noise and checks that a value between 1 and -1 is got.
TEST(PerlinNoise, 2DPerlinNoise)
{
    // Create a Perlin noise object
    siv::PerlinNoise perlin;

    // Generate a 2D noise value at coordinates (0.5, 0.5)
    double noiseValue = perlin.noise2D(0.5, 0.5);

    // Check that the noise value is within the expected range
    EXPECT_GE(noiseValue, -1.0);
    EXPECT_LE(noiseValue, 1.0);
}

/// @brief Tests the generation of 3D Perlin noise.
/// @detail Tests by checking the WUV center of the generated noise and checks that a value between 1 and -1 is returned.
TEST(PerlinNoise, 3DPerlinNoise)
{
    // Create a Perlin noise object
    siv::PerlinNoise perlin;

    // Generate a 3D noise value at coordinates (0.5, 0.5, 0.5)
    double noiseValue = perlin.noise3D(0.5, 0.5, 0.5);

    // Check that the noise value is within the expected range
    EXPECT_GE(noiseValue, -1.0);
    EXPECT_LE(noiseValue, 1.0);
}
