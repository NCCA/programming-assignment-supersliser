//
// Created by thoma on 23/03/2025.
//
#include "system/MoveSystem.h"
#include <gtest/gtest.h>
#include <ngl/NGLInit.h>
#include <SDL2/SDL.h>

#include "Table.h"
#include "component/BlockComponents.h"
#include "component/CameraComponents.h"
#include "system/RenderWorldSystem.h"
#include "system/SetPositionSystem.h"
#include "system/ApplyBlockTextureSystem.h"
#include "utils.h"
#include "system/SetCameraLookSystem.h"
#include "system/MovePlayerSystem.h"


TEST(World, generateWorld) {
    Table world;
    for (uint32_t i = 0; i < 9; i++) {
        world.createEntity();
    }

    world.registerComponentType(TransformComponents::getComponentID());
    MoveSystem setPositionSystem;
    for (float i = -1; i <= 1; i++) {
        for (float j = -1; j <= 1; j++) {
            setPositionSystem.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&setPositionSystem, TransformComponents::getComponentID(), (i + 1) * 3 + (j + 1),
                      (i + 1) * 3 + (j + 1));
        }
    }
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(0)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[0] == ngl::Vec3(-1.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(1)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[1] == ngl::Vec3(-1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(2)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[2] == ngl::Vec3(-1.0f, 0.0f, 1.0f));
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(3)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[3] == ngl::Vec3(0.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(4)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[4] == ngl::Vec3(0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(5)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[5] == ngl::Vec3(0.0f, 0.0f, 1.0f));
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(6)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[6] == ngl::Vec3(1.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(7)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[7] == ngl::Vec3(1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponents *>(world.getEntity(8)[world.getComponentIndex(
            TransformComponents::getComponentID())].m_column.get())->m_ps[8] == ngl::Vec3(1.0f, 0.0f, 1.0f));
}

TEST(World, moveEntityInWorld) {
    Table world;
    for (uint32_t i = 0; i < 13; i++) {
        world.createEntity();
    }
    world.registerComponentType(TransformComponents::getComponentID());
    MoveSystem setPositionSystem;
    for (float i = -1; i <= 1; i++) {
        for (float j = -1; j <= 1; j++) {

            std::vector<float> args;
            setPositionSystem.i_pos = ngl::Vec3(i * 1, 0.0f, j * 1);
            world.run(&setPositionSystem, TransformComponents::getComponentID(), (i + 1) * 3 + (j + 1),
                      (i + 1) * 3 + (j + 1));
        }
    }
    setPositionSystem.i_pos = ngl::Vec3(1.0f, 1.0f, 0.0f);
    world.run(&setPositionSystem, TransformComponents::getComponentID(), 9, 9);
    setPositionSystem.i_pos = ngl::Vec3(-1.0f, 1.0f, 1.0f);
    world.run(&setPositionSystem, TransformComponents::getComponentID(), 10, 10);
    setPositionSystem.i_pos = ngl::Vec3(0.0f, 1.0f, 1.0f);
    world.run(&setPositionSystem, TransformComponents::getComponentID(), 11, 11);
    setPositionSystem.i_pos = ngl::Vec3(0.0f, 1.0f, 1.0f);
    world.run(&setPositionSystem, TransformComponents::getComponentID(), 12, 12);

    MoveSystem m;
    Table character;
    character.createEntity();
    character.registerComponentType(TransformComponents::getComponentID());
    setPositionSystem.i_pos = ngl::Vec3(0.0f, 1.0f, 0.0f);
    character.run(&setPositionSystem, TransformComponents::getComponentID());
    m.i_pos = ngl::Vec3(1.0f, 0.0f, 0.0f);
    m.i_world = &world;
    character.run(&m, TransformComponents::getComponentID());
    auto temp = static_cast<TransformComponents *>(character.getEntity(0)[1].m_column.get())->m_ps[0];
    EXPECT_TRUE(static_cast<TransformComponents *>(character.getEntity(0)[1].m_column.get())->m_ps[0] ==
                ngl::Vec3(0.0f, 1.0f, 0.0f));
    m.i_pos = ngl::Vec3(0.0f, 0.0f, -1.0f);
    m.i_world = &world;
    auto currentPos = static_cast<TransformComponents*>(character.getColumn(character.getComponentIndex(TransformComponents::getComponentID())).get())->m_ps[0];
    character.run(&m, TransformComponents::getComponentID());
    currentPos = static_cast<TransformComponents*>(character.getColumn(character.getComponentIndex(TransformComponents::getComponentID())).get())->m_ps[0];
    auto temp2 = static_cast<TransformComponents *>(character.getEntity(0)[1].m_column.get())->m_ps[0];
    EXPECT_TRUE(static_cast<TransformComponents *>(character.getEntity(0)[1].m_column.get())->m_ps[0] ==
                ngl::Vec3(0.0f, 1.0f, -1.0f));
}

TEST(WorldDisplay, WorldVisible) {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("World Visible TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
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
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    Table world;
    for (uint32_t i = 0; i < 1; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    ms.i_pos = ngl::Vec3(0.0f, 0.0f, 1.0f);
    world.run(&ms, TransformComponents::getComponentID());
    SetCameraLookSystem setCameraLookSystem;
    setCameraLookSystem.i_pos = ngl::Vec3(2.0f, 2.0f, 2.0f);
    setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
    players.run(&setCameraLookSystem, CameraComponents::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;


    while (!quit) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT :
                    quit = true;
                    break;

                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_ESCAPE :
                            quit = true;
                            break;
                        case SDLK_RETURN :
                            success = true;
                            quit = true;
                            break;
                        default :
                            break;
                    } // end of key process
                } // end of keydown

                    break;
                default :
                    break;
            } // end of event switch
        } // end of poll events

        // now we draw ngl
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        // std::cout << "Running World Visible Test, please press enter if you can see the world or escape otherwise: ";
        // swap the buffers
        SDL_GL_SwapWindow(window);

    }

    EXPECT_TRUE(success);
    // now tidy up and exit SDL
    SDL_Quit();
}


TEST(WorldDisplay, WorldMultiBlockVisible) {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("World MultiBlock Visible TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
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
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    Table players;
    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    Table world;
    for (uint32_t i = 0; i < 9; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;
    for (float i = -1; i <= 1; i++) {
        for (float j = -1; j <= 1; j++) {
            std::vector<float> args;
            ms.i_pos = ngl::Vec3(i * 1, 0.0f, j * 1);
            world.run(&ms, TransformComponents::getComponentID(), (i + 1) * 3 + (j + 1), (i + 1) * 3 + (j + 1));
        }
    }


    SetCameraLookSystem setCameraLookSystem;
    setCameraLookSystem.i_pos = ngl::Vec3(4.0f, 4.0f, 4.0f);
    setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
    players.run(&setCameraLookSystem, CameraComponents::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    applyBlockTextureSystem.i_blockType = BlockType::Grass;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID());
    for (float i = -1; i <= 1; i++) {
        for (float j = -1; j <= 1; j++) {
            world.createEntity();
            ms.i_pos = ngl::Vec3(i * 1, -1.0f, j * 1);
            world.run(&ms, TransformComponents::getComponentID(), 9 + (i + 1) * 3 + (j + 1), 9 + (i + 1) * 3 + (j + 1));
        }
    }
    applyBlockTextureSystem.i_blockType = BlockType::Dirt;
    world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), 9, 18);

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;


    while (!quit) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT :
                    quit = true;
                    break;

                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_ESCAPE :
                            quit = true;
                            break;
                        case SDLK_RETURN :
                            success = true;
                            quit = true;
                            break;
                        default :
                            break;
                    } // end of key process
                } // end of keydown

                    break;
                default :
                    break;
            } // end of event switch
        } // end of poll events

        // now we draw ngl
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        // std::cout << "Running World Visible Test, please press enter if you can see the world or escape otherwise: ";
        // swap the buffers
        SDL_GL_SwapWindow(window);

    }

    EXPECT_TRUE(success);
    // now tidy up and exit SDL
    SDL_Quit();
}

TEST(WorldDisplay, AllTextureTest)
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Or die on error
        printf("Unable to initialize SDL");
        return;
    }

    // now create our window
    SDL_Window *window = SDL_CreateWindow("All Texture TEST",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1080,
                                          720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
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
    // flag to indicate if we need to exit
    bool quit = false;
    // sdl event processing data structure
    SDL_Event event;
    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    constexpr int TEXTURE_COUNT = 7;

    Table players;
    Table world;
    for (uint32_t i = 0; i < TEXTURE_COUNT; i++) {
        world.createEntity();
    }
    world.registerComponentType(BlockComponents::getComponentID());
    world.registerComponentType(BlockTextureComponent::getComponentID());
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem ms;

    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());
    SetCameraLookSystem setCameraLookSystem;
    setCameraLookSystem.i_pos = ngl::Vec3(4.0f, 4.0f, 4.0f);
    setCameraLookSystem.i_look = ngl::Vec3(0.0f, 0.0f, 0.0f);
    players.run(&setCameraLookSystem, CameraComponents::getComponentID());

    ApplyBlockTextureSystem applyBlockTextureSystem;
    for (int i = 0; i < TEXTURE_COUNT; i++) {
        ms.i_pos = ngl::Vec3(i - TEXTURE_COUNT / 2, 0.0f, 0.0f);
        world.run(&ms, TransformComponents::getComponentID(), i, i);
        applyBlockTextureSystem.i_blockType = static_cast<BlockType>(i);
        world.run(&applyBlockTextureSystem, BlockTextureComponent::getComponentID(), i, i);
    }

    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;

    bool success = false;


    while (!quit) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // this is the window x being clicked.
                case SDL_QUIT :
                    quit = true;
                    break;

                    // now we look for a keydown event
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        // if it's the escape key quit
                        case SDLK_ESCAPE :
                            quit = true;
                            break;
                        case SDLK_RETURN :
                            success = true;
                            quit = true;
                            break;
                        default :
                            break;
                    } // end of key process
                } // end of keydown

                    break;
                default :
                    break;
            } // end of event switch
        } // end of poll events

        // now we draw ngl
        players.run(&renderWorldSystem, CameraComponents::getComponentID());
        // std::cout << "Running World Visible Test, please press enter if you can see the world or escape otherwise: ";
        // swap the buffers
        SDL_GL_SwapWindow(window);

    }

    EXPECT_TRUE(success);
    // now tidy up and exit SDL
    SDL_Quit();
}