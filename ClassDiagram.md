@startuml

class Table {
	# Vector<Column<Component>> m_columns
	+ void registerComponentType(T& i_componentType)
	+ void addComponent(T& i_component, Entity i_entity)
	+ void removeComponent(T& i_componentType, Entity i_entity)
	+ void run(System& i_system, uint32_t i_componentID)
	+ Entity createEntity()
}

abstract class Component {
	+ unsigned int32 m_id
}

class TransformComponent {
	+ vec3 m_position
	+ vec3 m_rotation
	+ vec3 m_scale
}

abstract class System {
	+ virtual void run(a_Component& i_component);
}

Table o-- System : "Applied To Components by"
Component <|-- TransformComponent : "Inherits From"
Table o-- Component : "Contains multiple"

@enduml