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
	+ {virtual} void run(T& i_component, int i_index);
}

class MoveSystem {
	+ void run(PositionComponent i_position, int i_index)
}



Table "1" *-- "0..*" Column : "Contains multiple"
Column o.. PositionComponent : "Could Point to a"
Column o.. Entity : "Could Point to an"
System <|-- MoveSystem : "Inherits with T = PositionComponent"
Table o-- System : "Runs"

@enduml