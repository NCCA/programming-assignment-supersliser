# Adding Components

To add a component to the ECS, please follow the following steps:

## Create Header File
Create a new header file in the `include/component` directory, postfix the name with `Component.h`. For example, if you are creating a `Transform` component, the file should be named `TransformComponent.h`.

The header file should contain the following:

```cpp
class ClassName {
public:
    Constructor(size_t i_size);
    std::vector<datatype> m_data;
    statis std::uint8_t getComponentID() { return a_static_number; }
};
```

## Create Source File
Create a new source file in the `src/component` directory, postfix the name with `Component.cpp`. For example, if you are creating a `Transform` component, the file should be named `TransformComponent.cpp`.
The source file should contain the following:

```cpp
#include "component/ClassName.h"

Constructor(size_t i_size) {
    for (size_t i = 0; i < i_size; ++i) {
        m_data.push_back(datatype(default_value));
    }
}
```

## Update the Table Class
In `Table.cpp`, update the `registerComponentType` function and the `createEntity` function to handle the case of your given ComponentID.
```cpp
// for the registerComponentType function
case componentID:
    m_columns.push_back({i_componentType, std::make_shared<IsSprintingComponent>(static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount())});
    break;

// for the createEntity function
case componentID:
    static_cast<ClassName*>(m_columns[i].m_column.get())->m_data.push_back(default_value);
    // repeat for all component vectors
    break;  
```