//
// Created by s5605187 on 22/03/25.
//

#include <gtest/gtest.h>
#include <ngl/NGLInit.h>

#include "Table.h"
#include "system/SetPositionSystem.h"
#include <SDL2/SDL.h>

#include "utils.h"

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
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN
    );
    // check to see if that worked or exit
    if (!window) {
        printf("Unable to create window");
        return;
    }

    // Create our opengl context and attach it to our window

    SDL_GLContext glContext = utils::createOpenGLContext(window);
    if (!glContext) {
        printf("Problem creating OpenGL context ");
        return;
    }
    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(window, glContext);
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::initialize();
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    Table table;
    uint32_t entity = table.createEntity();
    table.registerComponentType(TransformComponents::getComponentID());
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    table.registerComponentType(TransformComponents::getComponentID());
    EXPECT_EQ(table.getEntity(entity).size(), 2);

    uint32_t entity2 = table.createEntity();
    EXPECT_EQ(table.getEntity(entity2).size(), 2);
}

TEST(System, RunSystem) {
    Table table;
    for (uint32_t i = 0; i < 10; i++) {
        table.createEntity();
    }
    table.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem moveSystem;
    moveSystem.i_pos = ngl::Vec3{1.0f, 0.0f, 0.0f};
    table.run(&moveSystem, 2);
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        auto* positionComponent = static_cast<TransformComponents*>(entity3[table.getComponentIndex(TransformComponents::getComponentID())].m_column.get());
        EXPECT_EQ(positionComponent->m_ps[i].m_x, 1.0f);
    }

    for (uint32_t i = 0; i < 10; i++)
    {
        table.createEntity();
    }
    table.run(&moveSystem, TransformComponents::getComponentID());
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        int index = table.getComponentIndex(TransformComponents::getComponentID());
        TransformComponents* positionComponent = static_cast<TransformComponents*>(entity3[index].m_column.get());
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 1.0f);
    }
    for (uint32_t i = 10; i < 20; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        TransformComponents* positionComponent = static_cast<TransformComponents*>(entity3[table.getComponentIndex(TransformComponents::getComponentID())].m_column.get());
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 1.0f);
    }
    moveSystem.i_pos = ngl::Vec3{0.0f, 0.0f, 0.0f};
    table.run(&moveSystem, TransformComponents::getComponentID());
    moveSystem.i_pos = ngl::Vec3{1.0f, 0.0f, 0.0f};
    table.run(&moveSystem, TransformComponents::getComponentID(), 10, 20);
    for (uint32_t i = 0; i < 10; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        int index = table.getComponentIndex(TransformComponents::getComponentID());
        TransformComponents* positionComponent = static_cast<TransformComponents*>(entity3[index].m_column.get());
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 0.0f);
    }
    for (uint32_t i = 10; i < 20; i++) {
        std::vector<Column> entity3 = table.getEntity(i);
        TransformComponents* positionComponent = static_cast<TransformComponents*>(entity3[table.getComponentIndex(TransformComponents::getComponentID())].m_column.get());
        EXPECT_FLOAT_EQ(positionComponent->m_ps[i].m_x, 1.0f);
    }
}