# Thomas Lower CFGAA Assignment
> s5605187
> [!NOTE]
> Any graphics created in this project were likely generated using [PlantUML](https://plantuml.com/)

## Idea

The basis of this project is to create a voxel based world generator which could later be used to house a colony management style game. The game will feature a first person character controlled using the keyboard and mouse, with a voxel world which can be explored.

## Initial Research

The research for this project can be realistically split into 2 sections. The first of which being the creation of a games engine within which the game can run. The second is a voxel world where the world is made of blocks of equal size.

### Entity Component System

> References [Sander Mertens ECS FAQ](https://github.com/SanderMertens/ecs-faq) and [Austin Morlan's Bitwise ECS Guide](https://austinmorlan.com/posts/entity_component_system/)

The first part of research was to study how previous games engines run their games. The most common design pattern for a game engine is the Entity Component System (ECS). Details regarding this could be found [here](https://github.com/SanderMertens/ecs-faq).

The ECS pattern works by splitting the game into 3 parts:
- **Entity**: THe individual objects in the game.
- **Component**: The data which is associated with the entity.
- **System**: The logic which is applied to the data in the component.

Within this, there are 3 main ways of laying out this data to optimise different situations:

- **Table-Based ECS**: This is where data is grouped by component type, essentially forming a table where columns are components and rows are entities. This is optimised for running systems on individual component types across all entites.
- **Discrete ECS**: This is where data is grouped by entity, esentially an entity would just be a pointer to a list of components. This is optimised for adding and removing entities.
- **Bitwise ECS**: This is where data is grouped by entity, but the components are stored as a bitmask. This is optimised for fast lookups of entities with specific components.

Ultimately, I have opted to use a Table-Based ECS due to the facts that: it is the most common design pattern used by many large games engines (such as Unreal Engine and Unity) and is optimised for applying systems to data efficiently making it useful for managing a world of blocks which have the same components, as well as applying movement and simulation logic to the eventual Colony Management game that would be implemented later.

> [!NOTE]
> For studying the specifics of how an ECS could be implemented within modern C++, I made use of Austin Morlan's guide on the subject. This was very useful as an introduction to the concept however required massive alteration to be applicable as it uses a Bitwise ECS. The full guide can be found [here](https://austinmorlan.com/posts/entity_component_system/).

### Voxel World

> References [Learn OpenGL Instancing](https://learnopengl.com/Advanced-OpenGL/Instancing), [Learn OpenGL Textures](https://learnopengl.com/Getting-started/Textures) and [Minecraft](https://www.minecraft.net/en-us)

The second part of my research was to study how to display a collection of cubes efficiently. The basic logic of a voxel based world seemed simple enough to interpret, it takes advantage of a concept known as **instancing**.

> Instancing is the process of creating multiple "copies" of an object where each object is simply a reference to a base mesh with a change in transformation.

This is useful for a voxel world as it allows for the creation of a large number of cubes without having to create a new mesh for each cube. This is done by creating a single cube mesh and then applying a transformation to each instance of the cube to place it in the correct location. However, this is still slow to run on the CPU. As such, to truly optimise this for real time applications, it requires the creation custom shading code to run on the GPU. This allows the base mesh to be loaded
along with a list of positions to create the instances of the mesh.

To study how this can be practically achieved, I used a guide from Learn OpenGL which walks through the process of creating instances, although the example this uses is asteroids which - most notably - all have identical textures (Full Guide found [here](https://learnopengl.com/Advanced-OpenGL/Instancing)). This is not true of blocks in a voxel world.

The issue with, what I will refer to as, true instancing is that it is a binary system, you are either entirely using it, or not using it at all. This meant that, in order to maintain the performance gains from shader GPU based instancing, I had to figure out how to instance the textures as well as the locations. To achieve this, I made sure that all textures were loaded on start and then an index to the correct texture was passed to instances along with the position.

> [!NOTE]
> For studying the basics of how to apply textures which then applied my solve using indexs passed to instances was inspired by the Learn OpenGL guide on Textures. The full guide can be found [here](https://learnopengl.com/Getting-started/Textures)

Another important point of research is the most famous voxel game **[Minecraft](https://www.minecraft.net/en-us)**. This is specifically useful for discussing the concept of world generation. Minecraft uses a system called perlin noise to generate the components of the world, due to a lack of specific blocks and biome mechanics, I will just be using 1 instance of this noise to calculate the height of the world at a given point. Grass will be placed at the top with dirt some distance below that
and stone some distance below that. This is a simple system which allows for the generation of a world which is not flat, but also not too complex.

> [!NOTE]
> More details on world generation in minecraft can be found [here](https://minecraft.wiki/w/World_generation)

## Project Structure

![/docs/ClassDiagram.png](https://github.com/NCCA/programming-assignment-supersliser/blob/docs/docs/ClassDiagram.png?raw=true)

Above is a class diagram to describe the basic ideas behind how the project is structured and various classes link together.

> [!NOTE]
> The above diagram does not show all components and systems, rather it demonstrates the basic ideas, of which you can assume other components and systems will follow similar patterns. To view a full UML, see [docs/FullUML.png](https://github.com/NCCA/programming-assignment-supersliser/blob/docs/docs/fullUML.png?raw=true)
