@startuml
struct vec3
struct vec2
enum e_job {
	UNEMPLOYED
	WHEAT_FARMER
	MINER
	MILLER
	BAKER
	GUARD
}
abstract class a_ObjectEntity {
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
	+ void deselect()
	+ vec3 position()
	+ a_ObjectEntity()
	+ a_ObjectEntity(vec3 i_position, bool i_visible = true, bool i_selectable = true)
	+ ~a_ObjectEntity()
}

vec3 <.. a_ObjectEntity

abstract class a_MoveableEntity {
	# vec3 m_direction
	# int m_speed
	# int m_health
	# int m_maxHealth
	# bool m_inAir
	+ void setDirection(vec3 i_direction)
	+ void rotate(vec3 i_axis, int i_rotation)
	+ void directionAngle(vec3 i_axis)
	+ vec3 direction()
	+ void setSpeed(int i_speed)
	+ int speed()
	+ void damage(int i_damage)
	+ void heal(int i_healing)
	+ int health()
	+ a_MoveableEntity()
	+ a_MoveableEntity(vec3 i_position, vec3 i_direction = (0,0,1), int i_health = 100, int i_speed = 1, int i_visible = true, int i_selectable = true)
	+ ~a_MoveableEntity()
	+ void jump()
	+ void setInAir(bool i_inAir)
	+ bool inAir()
	+ vec3 getMovementVector(vec2 i_direction)
}

a_ObjectEntity <|-- a_MoveableEntity
vec3 <.. a_MoveableEntity

class PlayerEntity {
	# Camera m_cam
	# bool m_sprinting
	# int m_stamina
	# s_Colony m_colony
	+ PlayerEntity()
	+ PlayerEntity(vec3 i_position, vec3 i_rotation, int i_health)
	+ void startSprint()
	+ void stopSprint()
	+ void move(vec2 i_direction)
	+ int stamina()
	+ void setStamina(int i_stamina)
	+ setColony(s_Colony* i_colony)
	+ s_Colony* colony()
	+ ~PlayerEntity
}

a_MoveableEntity <|-- PlayerEntity
vec3 <.. PlayerEntity
s_Colony o-- PlayerEntity
Camera o-- PlayerEntity
vec2 <.. PlayerEntity

class ColonistEntity {
	# s_Colony* m_colony
	# e_job m_job
	+ void hire(e_job i_job)
	+ void fire()
	+ e_job job()
	+ void setColony(s_Colony* i_colony)
	+ ColonistEntity()
	+ ColonistEntity(e_job i_job)
	+ void move(vec2 i_direction)
	+ ColonistEntity(vec3 i_position, vec3 i_direction, e_job i_job)
	+ ~ColonistEntity()
}

a_MoveableEntity <|-- ColonistEntity
s_Colony o-- ColonistEntity
e_job <.. ColonistEntity
vec3 <.. ColonistEntity
vec2 <.. ColonistEntity

abstract class a_item {
	# e_item m_item
	+ {abstract} void use()
	+ string name()
	+ ~a_item()
}

e_item <.. a_item

abstract class PlaceableItem {
	# PlacedEntity m_placedItem
	+ void use()
	+ {static} PlaceableItem createItem(int i_id)
	+ PlaceableItem()
	+ PlaceableItem(string i_name, int i_id)
	+ ~PlaceableItem()
}

a_item <|-- PlaceableItem
PlacedEntity o-- PlaceableItem

class Grass {
	+ Grass()
	+ void use()
}

PlaceableItem <|-- Grass

class Log {
	+ Log()
	+ void use()
}

PlaceableItem <|-- Log

class Leaves {
	+ Leaves()
	+ void use()
}

PlaceableItem <|-- Leaves

class Stone {
	+ Stone()
	+ void use()
}

PlaceableItem <|-- Stone

class Planks {
	+ Planks()
	+ void use()
}

PlaceableItem <|-- Planks

abstract class UseableItem {
+ void use()
+ {static} UseableItem createItem(int i_id)
+ UseableItem()
+ UseableItem(string i_name, int i_id)
+ ~UseableItem()
}

a_item <|-- UseableItem

class Bow {
	+ Bow()
	+ void use()
}

UseableItem <|-- Bow

class Arrow {
	+ Arrow()
	+ void use()
}

UseableItem <|-- Arrow

class Slot {
	# a_item m_item
	# int m_quantity
	# int m_maxItems
	+ void setItem(a_Item i_item);
	+ a_item item()
	+ void setQuantity(int i_quantity)
	+ int quantity()
	+ Slot()
	+ Slot(a_item i_item = 0, i_quantity = 1, i_maxItems = 64)
	+ ~Slot()
}

a_item o-- Slot

class Inventory {
	# vec<Slot> m_slots
	# int m_selctedItemIndex
	# bool m_moving
	+ void addItem(a_item i_item, int i_quantity)
	+ void removeItem(a_Item i_item, int i_quantity)
	+ Slot getItem()
	+ void startMoveItem()
	+ void moveItem(Slot* i_slot)
	+ void stopMoveItem()
	+ void selectItem(i_itemNum)
	+ Inventory()
	+ ~Inventory
}

Slot o-- Inventory
a_item o-- Inventory

class FillableInventory {
	# int m_maxItems
	+ void addItem(a_item i_item, int i_quantity)
	+ FillableInventory()
	+ FillableInventory(int i_maxItems)
	+ ~FillableInventory
}

Inventory <|-- FillableInventory
a_item o-- FillableInventory

class Hotbar {
	+ void selectItem(int i_itemNum)
	+ void nextItem()
	+ void prevItem()
	+ Hotbar()
	+ ~Hotbar()
}

FillableInventory <|-- Hotbar

class Camera {
	# float m_fov
	# float m_closeCullingDistance
	# float m_farCullingDistance
	# float m_aspectRatio
	+ void setFOV(float i_fov)
	+ float fov()
    + void setAspectRatio(float i_aspectRatio)
	+ float aspectRatio()
	+ Camera()
	+ Camera(int i_closeCullingDistance, int i_farCullingDistance, float i_fov, float i_aspectRatio)
	+ void Draw(vec3 i_position, vec3 i_direction, vec3 i_up)
	+ ~Camera()
}
class PlacedEntity {
	# e_placeableItem m_item
	+ string name()
	+ void break()
	+ void use()
	+ PlacedEntity()
	+ PlacedEntity(e_placeableItem i_item)
	+ ~PlacedEntity()
}

a_ObjectEntity <|-- PlacedEntity

class ColonyBanner {
	+ void break()
	+ void use()
	+ ColonyBanner()
	+ ~ColonyBanner
}

PlacedEntity <|-- ColonyBanner

class S_World {
	# PlayerEntity m_player
	# Vec<PlacedEntity> m_blocks
	+ void spawnPlayer()
	+ void loadPlayer(PlayerEntity i_player)
	+ void respawnPlayer()
	+ void killPlayer()
	+ void placeBlock(PlacedEntity i_block, vec3 i_position)
	+ void breakBlock(vec3 i_position)
	+ S_World()
	+ S_World {static} loadWorld()
}

PlayerEntity o-- S_World
PlacedEntity o-- S_World

class s_Colony {
	# Inventory m_inventory
	# ColonyBanner m_banner
	# Vec<ColonistEntity> m_colonists
	# vec3 m_size
	# {static} s_World m_world
	+ void addItemToInventory(Slot i_item)
	+ void pickupItem(a_item i_item)
	+ ColonyBanner banner()
	+ Vec<Slot> items()
	+ spawnColonist()
	+ killColonist(ColonistEntity i_colonist)
	+ hireColonist(e_job i_job, ColonistEntity i_colonist)
	+ fireColonist(ColonistEntity i_colonist)
}

Inventory o-- s_Colony
ColonyBanner o-- s_Colony
ColonistEntity o-- s_Colony
vec3 <.. s_Colony
Slot o-- s_Colony
a_item o-- s_Colony
e_job <.. s_Colony
@enduml