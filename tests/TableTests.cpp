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

TEST(Table, AddEntity) {
    Table table;
    uint32_t entity = table.createEntity();
    EXPECT_EQ(entity, 0);
    uint32_t entity2 = table.createEntity();
    EXPECT_EQ(entity2, 1);
}

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