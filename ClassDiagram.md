@startuml
struct vec3
struct quarternion
enum e_job {
	UNEMPLOYED
	WHEAT_FARMER
	MINER
	MILLER
	BAKER
	GUARD
}
enum e_item {
	NULL_ITEM
	DIRT
	GRASS
	LOG
	WOOD
	LEAVES
	BOW
	ARROW
}
enum e_placeableItem {
	NULL_ITEM
	GRASS
	STONE
	LOG
	PLANKS
	LEAVES
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
	+ ObjectEntity()
	+ ObjectEntity(vec3 i_position, bool i_visible = true, bool i_selectable = true)
	+ ~ObjectEntity()
}

vec3 <.. ObjectEntity

abstract class a_MoveableEntity {
	# quarternion m_rotation
	# int m_speed
	# int m_health
	# int m_maxHealth
	+ void setRotation(vec3 i_rotation)
	+ void setRotation(quarternion i_rotation)
	+ void rotate(vec3 i_axis, int i_rotation)
	+ quarternion Qrotation()
	+ vec3 Vrotation()
	+ void setSpeed(int i_speed)
	+ int speed()
	+ void damage(int i_damage)
	+ void heal(int i_healing)
	+ int health()
	+ MoveableEntity()
	+ MoveableEntity(vec3 i_position, vec3 i_rotation = (0,0,1), int i_health = 100, int i_speed = 1, int i_visible = true, int i_selectable = true)
	+ ~MoveableEntity()
}

ObjectEntity <|-- MoveableEntity
quarternion <.. MoveableEntity
vec3 <.. MoveableEntity

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
	+ setColony(s_Colony i_colony)
	+ s_Colony colony()
	+ ~PlayerEntity
}

MoveableEntity <|-- PlayerEntity
vec3 <.. PlayerEntity
s_Colony o-- PlayerEntity
Camera o-- PlayerEntity

class ColonistEntity {
	# {static} s_Colony m_colony
	# e_job m_job
	+ void hire(e_job i_job)
	+ void fire()
	+ e_job job()
	+ ColonistEntity()
	+ ColonistEntity(e_job i_job)
	+ ColonistEntity(vec3 i_position, vec3 i_rotation, e_job i_job)
	+ ~ColonistEntity()
}

MoveableEntity <|-- ColonistEntity
s_Colony o-- ColonistEntity
e_job <.. ColonistEntity
vec3 <.. ColonistEntity

abstract class Item {
	# e_item m_item
	+ {abstract} void use()
	+ string name()
	+ {static} Item createItem(e_item i_item)
	+ ~Item()
}

e_item <.. Item

abstract class PlaceableItem {
	+ void use()
	+ {static} PlaceableItem createItem(e_item i_item)
}

Item <|-- PlaceableItem
e_item <.. PlaceableItem

abstract class UseableItem {
	+ void use()
	+ {static} UseableItem createItem(e_item i_item)
}

Item <|-- UseableItem
e_item <.. UseableItem

class Slot {
	# Item m_item
	# int m_quantity
	# int m_maxItems
	+ void setItem()
	+ Item item()
	+ void setQuantity()
	+ int quantity()
	+ Slot()
	+ Slot(Item i_item = 0, i_quantity = 0, i_maxItems = 255)
	+ ~Slot()
}

Item o-- Slot

class Inventory {
	# vec<Slot> m_slots
	# int m_selctedItemIndex
	+ void addItem(Item i_item, int i_quantity)
	+ Slot getItem()
	+ void startMoveItem()
	+ void finishMoveItem()
	+ void selectItem(i_itemNum)
	+ Inventory()
	+ Inventory(vec<Slot> i_items)
	+ ~Inventory
}

Slot o-- Inventory
Item o-- Inventory

class FillableInventory {
	# int m_maxItems
	+ void addItem(Item i_item, int i_quantity)
	+ FillableInventory()
	+ FillableInventory(int i_maxItems)
	+ ~FillableInventory
}

Inventory <|-- FillableInventory
Item o-- FillableInventory

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
	+ Camera(int i_closeCullingDistance, int i_farCullingDistance, float i_fov)
	+ void Draw(vec3 i_position, quarternion i_direction)
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

ObjectEntity <|-- PlacedEntity
e_placeableItem <.. PlacedEntity

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
	+ void addItemToInventory(Slot i_item)
	+ void pickupItem(Item i_item)
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
Item o-- s_Colony
e_job <.. s_Colony
@enduml