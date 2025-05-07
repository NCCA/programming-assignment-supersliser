cmake_minimum_required(VERSION 3.12)

# -------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
# to build see the NGL instructions
# Windows :- mkdir build; cd build ; cmake -DCMAKE_PREFIX_PATH=~/NGL/ .. ; cmake --build .
# Linux / Mac mkdir build; cd build; cmake -DCMAKE_PREFIX_PATH~/NGL/ .. ; make
# -------------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# Name of the project
project(ColonyManagerBuild)

# This is the name of the Exe change this and it will change everywhere
set(TargetName ColonyGame)

# This will include the file NGLConfig.cmake, you need to add the location to this either using
# -DCMAKE_PREFIX_PATH=~/NGL or as a system environment variable.
find_package(NGL CONFIG REQUIRED)

# Now include the SDL libraries, which need to be installed using vcpkg
find_package(SDL2 CONFIG REQUIRED)

# use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Set the name of the executable we want to build
add_executable(${TargetName}
        src/main.cpp
        src/system/TestIsBlockedSystem.cpp
        include/component/TransformComponents.h
        include/Table.h
        include/system/System.h
        src/Table.cpp
        include/component/Entities.h
        src/component/Entities.cpp
        include/component/Column.h
        src/component/TransformComponents.cpp
        include/system/SetPositionSystem.h
        src/system/SetPositionSystem.cpp
        include/component/BlockComponents.h
        src/component/BlockComponents.cpp
        include/system/RenderWorldSystem.h
        src/system/RenderWorldSystem.cpp
        src/component/CameraComponents.cpp
        include/component/BlockTextureComponent.h
        src/component/BlockTextureComponent.cpp
        include/system/ApplyBlockTextureSystem.h
        src/system/ApplyBlockTextureSystem.cpp
        src/Camera.cpp
        include/component/BlockType.h
        include/Utils.h
        src/Utils.cpp
        include/dir.h
        include/system/SetCameraLookSystem.h
        src/system/SetCameraLookSystem.cpp
        include/system/MovePlayerSystem.h
        src/system/MovePlayerSystem.cpp
        src/system/RotateCameraSystem.cpp
        include/system/RotateCameraSystem.h
        include/component/IsSprintingComponent.h
        src/component/IsSprintingComponent.cpp
        include/system/SetSprintingSystem.h
        include/system/ToggleSprintingSystem.h
        src/system/SetSprintingSystem.cpp
        src/system/ToggleSprintingSystem.cpp
        include/component/SpeedComponent.h
        src/component/SpeedComponent.cpp
        include/system/PlayerFallSystem.h
        src/system/PlayerFallSystem.cpp
        PerlinNoise/PerlinNoise.hpp
        src/GenerateWorld.cpp
        include/GenerateWorld.h
        src/system/SetPlayerPositionSystem.cpp
        include/system/SetPlayerPositionSystem.h
        include/SDLWindowManager.h
        src/SDLWindowManager.cpp
        include/component/ChunkComponent.h
)
# Add NGL include path
include_directories(include $ENV{HOME}/NGL/include include/ PerlinNoise/)
target_sources(${TargetName} PRIVATE ${PROJECT_SOURCE_DIR}/src/main.cpp
)

# need to add some exta libs for SDL under linux
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(${TargetName} PRIVATE -lX11 -lXext)
endif()

target_link_libraries(${TargetName} PRIVATE NGL)

# Link in the SDL2 libraries
target_link_libraries(${TargetName} PRIVATE SDL2::SDL2)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(Tests
        tests/TableTests.cpp
        tests/SDLTest.cpp
        tests/WorldTests.cpp
        tests/PlayerTests.cpp
        tests/PlayerStepTests.cpp
        tests/NoiseTests.cpp
        tests/GenerateWorldTests.cpp
        src/system/TestIsBlockedSystem.cpp
        include/component/TransformComponents.h
        include/Table.h
        include/system/System.h
        src/Table.cpp
        include/component/Entities.h
        src/component/Entities.cpp
        include/component/Column.h
        src/component/TransformComponents.cpp
        include/system/SetPositionSystem.h
        src/system/SetPositionSystem.cpp
        include/component/BlockComponents.h
        src/component/BlockComponents.cpp
        include/system/RenderWorldSystem.h
        src/system/RenderWorldSystem.cpp
        src/component/CameraComponents.cpp
        include/component/BlockTextureComponent.h
        src/component/BlockTextureComponent.cpp
        include/system/ApplyBlockTextureSystem.h
        src/system/ApplyBlockTextureSystem.cpp
        src/Camera.cpp
        include/component/BlockType.h
        include/Utils.h
        src/Utils.cpp
        include/dir.h
        include/system/SetCameraLookSystem.h
        src/system/SetCameraLookSystem.cpp
        include/system/MovePlayerSystem.h
        src/system/MovePlayerSystem.cpp
        src/system/RotateCameraSystem.cpp
        include/system/RotateCameraSystem.h
        include/component/IsSprintingComponent.h
        src/component/IsSprintingComponent.cpp
        include/system/SetSprintingSystem.h
        include/system/ToggleSprintingSystem.h
        src/system/SetSprintingSystem.cpp
        src/system/ToggleSprintingSystem.cpp
        include/component/SpeedComponent.h
        src/component/SpeedComponent.cpp
        include/system/PlayerFallSystem.h
        src/system/PlayerFallSystem.cpp
        PerlinNoise/PerlinNoise.hpp
        src/GenerateWorld.cpp
        include/GenerateWorld.h
        src/system/SetPlayerPositionSystem.cpp
        include/system/SetPlayerPositionSystem.h
        include/SDLWindowManager.h
        src/SDLWindowManager.cpp
        include/component/ChunkComponent.h
)
include_directories(include)
target_sources(Tests PRIVATE)
target_link_libraries(Tests PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(Tests PRIVATE NGL)
target_link_libraries(Tests PRIVATE SDL2::SDL2)
gtest_discover_tests(Tests)

add_custom_target(${TargetName}CopyShaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${TargetName}>/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:${TargetName}>/textures
)