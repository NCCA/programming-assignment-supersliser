//
// Created by tom on 3/20/25.
//
#include "../include/MoveableEntity.h"

#include <ngl/Vec3.h>
#include "../include/ObjectEntity.h"


void a_MoveableEntity::setDirection(const ngl::Vec3& i_direction)
{
    m_direction = i_direction;
}

void a_MoveableEntity::rotate(const ngl::Vec3 i_axis, const int i_rotation)
{
    float radians = i_rotation * M_PI / 180.0f;
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);

    ngl::Vec3 rotatedVector = m_direction * cosTheta +
                              i_axis.cross(m_direction) * sinTheta +
                              i_axis * (i_axis.dot(m_direction) * (1 - cosTheta));
    m_direction = rotatedVector;
}

ngl::Vec3 a_MoveableEntity::direction() const
{
    return m_direction;
}
void a_MoveableEntity::setSpeed(const int i_speed)
{
    m_speed = i_speed;
}

int a_MoveableEntity::speed() const
{
    return m_speed;
}

void a_MoveableEntity::damage(const int i_damage)
{
    m_health -= i_damage;
    if (m_health < 0)
    {
        m_health = 0;
    }
}

void a_MoveableEntity::heal(const int i_healing)
{
    m_health += i_healing;
    if (m_health > m_maxHealth)
    {
        m_health = m_maxHealth;
    }
}

int a_MoveableEntity::health() const
{
    return m_health;
}

a_MoveableEntity::a_MoveableEntity(ngl::Vec3 i_position, ngl::Vec3 i_direction, int i_health, int i_speed, bool i_visible, bool i_selectable)
{
    m_position = i_position;
    m_direction = i_direction;
    m_health = i_health;
    m_maxHealth = i_health;
    m_speed = i_speed;
    m_visible = i_visible;
    m_selectable = i_selectable;
    m_selected = false;
}
