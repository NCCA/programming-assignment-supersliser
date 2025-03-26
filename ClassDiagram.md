@startuml

class Table {
	# Vector<Column> m_columns
	+ void registerComponentType(unsigned int8 i_componentType)
	+ void run(System<T> i_system, unsigned int8 i_componentType)
    + vector<Column> getEntity(unsigned int32 i_entity)
    + int getComponentIndex(unsigned int8 i_componentType)
	+ Entity createEntity()
}

class Column {
    + unsigned int8 m_componentType
	+ pointer m_column
}

class PositionComponent {
	+ vector<Vec3> m_positions
    + {static} unsigned int8 getComponentType()
	+ PositionComponent(size_t i_size)
}

class Entity { 
	# vector<unsigned int32> m_entities
	+ {static} unsigned int8 getComponentType()
	+ void addEntity()
	+ unsigned int32 getEntityID(int i_index)
	+ int getEntityIndex(unsigned int32 i_entityID)
	+ void removeEntity(unsigned int32 i_entityID)
}

abstract class System {
	+ void run(T i_component, int i_index);
}

class MoveSystem {
	+ void run(PositionComponent i_position, int i_index)
    + Table* i_world
    + Vec3 m_pos
}

class TestIsBlockedSystem{
    + void run(PositionComponent i_position, int i_index)
    + Table* i_world
    + bool o_isBlocked
}



Table "1" o-- "0..*" Column : "Contains multiple"
Column "1" o.. "1" PositionComponent : "Could be pointed to by"
Column "1" o.. "1" Entity : "Could be pointed to by"
System <|-- MoveSystem : "Is Inherited from"
Table "1" o-- "*" System : "Runs"
System <|-- TestIsBlockedSystem : "Is Inherited from"
TestIsBlockedSystem "1" ..o "1" Table : "Points to a different"
MoveSystem "1" ..o "1" Table : "Points to a different"
MoveSystem o-- PositionComponent: "T="
TestIsBlockedSystem o-- PositionComponent: "T="

@enduml
