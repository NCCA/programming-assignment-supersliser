//
// Created by s5605187 on 22/03/25.
//

#include <gtest/gtest.h>
#include <ngl/NGLInit.h>
#include <SDL2/SDL.h>

#include "Table.h"
#include "system/SetPositionSystem.h"
#include "Utils.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/// @brief Tests if a table is able to have entities added to it
/// @detail When adding an entity to a table, it's ID is the index it was originally added to. For example, the first entity added to a table will have ID 0, the second will have ID 1 etc... This test checks that a table can have multiple entities assigned to it by checking the id's of each entity after they have been added to the table.
TEST(Table, AddEntity) {
    Table table;
    uint32_t entity = table.createEntity();
    EXPECT_EQ(entity, 0);
    uint32_t entity2 = table.createEntity();
    EXPECT_EQ(entity2, 1);
}

/// @brief Tests if a table is able to assign a component to an entity
/// @detail Components are associated with entities, therefore we must add an entity first, then we can attempt to add a component to the table which will create a component of that type for each entity in the table. This test also checks that, after a component is registered with a table, any entities added afterwards will also have this component.
/// @note You may notice that this tests initialises SDL but never actually uses it, this is to because the component used for this test, Transform Component, relies on SDL and OpenGL to be able to update VBO instance locations, without having this active, the test will crash due to attempting to access the OpenGL systems which are not initialised.
TEST(Table, AddComponent) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return;
    }
    SDL_Window *window = SDL_CreateWindow("TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN
    );
    if (!window) {
        printf("Unable to create window");
        return;
    }
    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1);
    ngl::NGLInit::initialize();
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    Table table;
    table.createEntity();
    table.registerComponentType(TransformComponents::getComponentID());
    EXPECT_EQ(table.getComponentCount(), 2);

    table.registerComponentType(TransformComponents::getComponentID());
    EXPECT_EQ(table.getComponentCount(), 2);

    table.createEntity();
    EXPECT_EQ(table.getComponentCount(), 2);
}


/// @brief Tests if a table is able to run a system on a set of components, each assigned to entities
/// @detail When a system is run on a table, the function is able to specify a specific subset of entities to run this on, rather than running on all components of that type within the table. The user can also specify 1 individual component to run on by stating its index in both the start and end parameters of the function.
TEST(Table, RunSystem) {
    Table table;
    for (uint32_t i = 0; i < 10; i++) {
        table.createEntity();
    }
    table.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem moveSystem;
    moveSystem.i_pos = ngl::Vec3{1.0f, 0.0f, 0.0f};
    table.run(&moveSystem, TransformComponents::getComponentID());
    for (uint32_t i = 0; i < 10; i++) {
        TransformComponents* entity3 = static_cast<TransformComponents*>(table.getColumn(table.getComponentIndex(TransformComponents::getComponentID())).get());
        EXPECT_EQ(entity3->m_ps[i].m_x, 1.0f);
    }

    for (uint32_t i = 0; i < 10; i++)
    {
        table.createEntity();
    }
    table.run(&moveSystem, TransformComponents::getComponentID());
    for (uint32_t i = 0; i < 10; i++) {
        TransformComponents* entity3 = static_cast<TransformComponents*>(table.getColumn(table.getComponentIndex(TransformComponents::getComponentID())).get());
        EXPECT_EQ(entity3->m_ps[i].m_x, 1.0f);
    }
    for (uint32_t i = 10; i < 20; i++) {
        TransformComponents* entity3 = static_cast<TransformComponents*>(table.getColumn(table.getComponentIndex(TransformComponents::getComponentID())).get());
        EXPECT_EQ(entity3->m_ps[i].m_x, 1.0f);
    }
    moveSystem.i_pos = ngl::Vec3{0.0f, 0.0f, 0.0f};
    table.run(&moveSystem, TransformComponents::getComponentID());
    moveSystem.i_pos = ngl::Vec3{1.0f, 0.0f, 0.0f};
    table.run(&moveSystem, TransformComponents::getComponentID(), 10, 20);
    for (uint32_t i = 0; i < 10; i++) {
        TransformComponents* entity3 = static_cast<TransformComponents*>(table.getColumn(table.getComponentIndex(TransformComponents::getComponentID())).get());
        EXPECT_EQ(entity3->m_ps[i].m_x, 0.0f);
    }
    for (uint32_t i = 10; i < 20; i++) {
        TransformComponents* entity3 = static_cast<TransformComponents*>(table.getColumn(table.getComponentIndex(TransformComponents::getComponentID())).get());
        EXPECT_EQ(entity3->m_ps[i].m_x, 1.0f);
    }
}
