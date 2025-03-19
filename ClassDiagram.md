@startuml
struct vec3
struct quarternion
enum e_job {
	WHEAT_FARMER
	MINER
	MILLER
	BAKER
	GUARD
}
enum e_item {
	DIRT
	GRASS
	LOG
	WOOD
	LEAVES
	
}
abstract class ObjectEntity {
	# vec3 m_position
	# bool m_visible
	# bool m_selectable
	# bool m_selected
	+ void setPosition(vec3 i_position)
	+ void incrementPosition(vec3 i_increment)
	+ void incrementPosition(vec3 i_direction, int i_increment)
	+ void setVisible(bool i_visible)
	+ bool visible()
	+ void setSelectable(bool i_selectable)
	+ bool selected()
	+ void select()
	+ void unselect()
	+ vec3 position()
	+ ObjectEntity()
	+ ObjectEntity(vec3 i_position, bool i_visible = true, bool i_selectable = true)
	+ ~ObjectEntity()
}
abstract class MoveableEntity {
	# quarternion m_rotation
	# int m_speed
	# int m_health
	# int m_maxHealth
	+ void setRotation(vec3 i_rotation)
	+ void setRotation(float i_hRotation, float i_vRotation, vec3 i_upVector)
	+ void setRotation(quarternion i_rotation)
	+ quarternion rotation()
	+ vec3 rotation()
	+ void setSpeed(int i_speed)
	+ int speed()
	+ void damage(int i_damage)
	+ void heal(int i_healing)
	+ int health()
	+ MoveableEntity()
	+ MoveableEntity(vec3 i_position, vec3 i_rotation = (0,0,1), int i_health = 100, int i_speed = 100)
	+ ~MoveableEntity()
}
class PlayerEntity {
	# Camera m_cam
	+ PlayerEntity()
	+ PlayerEntity(vec3 i_position = (0,0,0), vec3 i_rotation = (0,0,1), i_health = 100)
	+ ~PlayerEntity
}
class ColonistEntity {
	# {static} HomeBanner m_home
	# e_job m_job
	+ void hire(e_job i_job)
	+ void fire()
	+ e_job job()
	# ColonistEntity()
	# ColonistEntity(e_job i_job)
	# ColonistEntity(vec3 i_position, vec3 i_rotation, e_job i_job)
}
abstract class Item {
	# e_item m_item
	+ {abstract} void use()
	+ {static} Item createItem(e_item i_item)
}
class PlaceableItem {
	+ void use()
	+ {static} Item createItem(e_item i_item)
}
class UseableItem {
	+ void use()
	+ {static} Item createItem(e_item i_item)
}
class Slot {
	# Item im_item
	# int m_quantity
}
class Inventory {
	# vec<Slot> m_slots
}
class FillableInventory {
	# int m_maxItems
}
class Hotbar {

}
class Camera {
	# float fov
	# int closeCullingDistance
	# int farCullingDistance
	+ void setFOV(float i_fov)
	+ float fov()
	+ Camera()
	+ Camera(int i_closeCullingDistance, int i_viewBoxSize, float i_fov)
	+ Camera(int i_closeCullingDistance, int i_farCullingDistance, float i_fov)
	+ Draw(vec3 i_position, quarternion i_direction)
	+ ~Camera()
}
class PlaceableEntity {

}
class ColonyBanner {

}

ObjectEntity <|-- MoveableEntity

MoveableEntity <|-- PlayerEntity
MoveableEntity <|-- ColonistEntity

ColonistEntity <.. e_job
ColonistEntity o-- FillableInventory

Item <|-- PlaceableItem
Item <|-- UseableItem
Item <.. e_item

Slot o-- Item
Inventory o-- Slot
Inventory <|-- FillableInventory
FillableInventory <|-- Hotbar

PlayerEntity o-- Camera
ObjectEntity o-- vec3
MoveableEntity o-- vec3
MoveableEntity o-- quarternion

PlaceableEntity <|-- ObjectEntity
PlaceableEntity <|-- ColonyBanner
@enduml