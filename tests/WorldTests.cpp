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

SDL_GLContext createOpenGLContext(SDL_Window *window)
{
    // Note you may have to change this depending upon the driver (Windows is fussy)
    // stick to 4.5 as the core base level for NGL works ok
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // set multi sampling else we get really bad graphics that alias
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    // on mac up to 32 will work but under linux centos build only 16
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // enable double buffering (should be on by default)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //
    return SDL_GL_CreateContext(window);

}

TEST(System, generateWorld)
{
    Table world;
    for (uint32_t i = 0; i < 9; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem setPositionSystem;
    for (float i = -1; i <= 1; i++)
    {
        for (float j = -1; j <= 1; j++)
        {
            setPositionSystem.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&setPositionSystem, TransformComponents::getComponentID(),  (i + 1) * 3 + (j + 1), (i + 1) * 3 + (j + 1));
        }
    }
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(0)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[0]==ngl::Vec3(-1.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(1)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[1]==ngl::Vec3(-1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(2)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[2]==ngl::Vec3(-1.0f, 0.0f, 1.0f));
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(3)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[3]==ngl::Vec3(0.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(4)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[4]==ngl::Vec3(0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(5)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[5]==ngl::Vec3(0.0f, 0.0f, 1.0f));
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(6)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[6]==ngl::Vec3(1.0f, 0.0f, -1.0f));
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(7)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[7]==ngl::Vec3(1.0f, 0.0f, 0.0f));
    EXPECT_TRUE(static_cast<TransformComponents*>(world.getEntity(8)[world.getComponentIndex(TransformComponents::getComponentID())].m_column.get())->m_ps[8]==ngl::Vec3(1.0f, 0.0f, 1.0f));
}

TEST(System, moveEntityInWorld)
{
    Table world;
    for (uint32_t i = 0; i < 12; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(TransformComponents::getComponentID());
    SetPositionSystem setPositionSystem;
    for (float i = -1; i <= 1; i++)
    {
        for (float j = -1; j <= 1; j++)
        {

            std::vector<float> args;
            setPositionSystem.i_pos = ngl::Vec3(i, 0.0f, j);
            world.run(&setPositionSystem, TransformComponents::getComponentID(), (i + 1) * 3 + (j + 1), (i + 1) * 3 + (j + 1));
        }
    }
    setPositionSystem.i_pos = ngl::Vec3(1.0f, 1.0f, 0.0f);
    world.run(&setPositionSystem, TransformComponents::getComponentID(), 9, 9);
    setPositionSystem.i_pos = ngl::Vec3(-1.0f, 1.0f, 1.0f);
    world.run(&setPositionSystem, TransformComponents::getComponentID(), 10, 10);
    setPositionSystem.i_pos = ngl::Vec3(0.0f, 1.0f, 1.0f);
    world.run(&setPositionSystem, TransformComponents::getComponentID(), 11, 11);

    MoveSystem m;
    Table character;
    character.createEntity();
    character.registerComponentType(TransformComponents::getComponentID());
    setPositionSystem.i_pos = ngl::Vec3(0.0f, 1.0f, 0.0f);
    character.run(&setPositionSystem, TransformComponents::getComponentID());
    m.i_pos = ngl::Vec3(1.0f, 0.0f, 0.0f);
    m.i_world = &world;
    character.run(&m, TransformComponents::getComponentID());
    EXPECT_TRUE(static_cast<TransformComponents*>(character.getEntity(0)[1].m_column.get())->m_ps[0] == ngl::Vec3(0.0f, 1.0f, 0.0f));
    m.i_pos = ngl::Vec3(0.0f, 0.0f, -1.0f);
    m.i_world = &world;
    character.run(&m, TransformComponents::getComponentID());
    EXPECT_TRUE(static_cast<TransformComponents*>(character.getEntity(0)[1].m_column.get())->m_ps[0] == ngl::Vec3(0.0f, 1.0f, -1.0f));
}

TEST(System, WorldVisible)
{
  // Initialize SDL's Video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    // Or die on error
    printf("Unable to initialize SDL");
      return;
  }

  // now get the size of the display and create a window we need to init the video
  SDL_Rect rect;
  SDL_GetDisplayBounds(0,&rect);
  // now create our window
  SDL_Window *window=SDL_CreateWindow("SDLNGL",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      rect.w/2,
                                      rect.h/2,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
                                     );
  // check to see if that worked or exit
  if (!window)
  {
    printf("Unable to create window");
      return;
  }

  // Create our opengl context and attach it to our window

   SDL_GLContext glContext=createOpenGLContext(window);
   if(!glContext)
   {
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
  bool quit=false;
  // sdl event processing data structure
  SDL_Event event;
  // now we create an instance of our ngl class, this will init NGL and setup basic
  // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
  // our gl stuff

    Table players;
    Table world;
    for (uint32_t i = 0; i < 9; i++)
    {
        world.createEntity();
    }
    world.registerComponentType(TransformComponents::getComponentID());
    world.registerComponentType(BlockComponents::getComponentID());
    players.createEntity();
    players.registerComponentType(CameraComponents::getComponentID());


    RenderWorldSystem renderWorldSystem;
    renderWorldSystem.i_world = &world;
    renderWorldSystem.i_cams = static_cast<CameraComponents*>(players.getEntity(0)[players.getComponentIndex(CameraComponents::getComponentID())].m_column.get());
    renderWorldSystem.run(static_cast<CameraComponents*>(players.getColumn(1)), 0);

    // now we draw ngl
      players.run(&renderWorldSystem, CameraComponents::getComponentID());
    // swap the buffers
    SDL_GL_SwapWindow(window);

    std::string userOutput;
    std::cout << "Running World Visible Test, please enter 1 if you can see the world: ";
    std::getline(std::cin, userOutput);
    EXPECT_TRUE(userOutput == "1");

  // now tidy up and exit SDL
 SDL_Quit();
}