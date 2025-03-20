//
// Created by tom on 3/20/25.
//
#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(ngl::Vec3 i_position, ngl::Vec3 i_direction, int i_health)
{
    m_position = i_position;
    m_direction = i_direction;
    m_health = i_health;
    m_maxHealth = 100;
    m_camera = Camera();
}

void PlayerEntity::startSprint()
{
    m_sprinting = true;
}

void PlayerEntity::stopSprint()
{
    m_sprinting = false;
}

void PlayerEntity::move(const ngl::Vec2& i_direction)
{
    auto direction = ngl::Vec3(i_direction.m_x, 0, i_direction.m_y);
    direction = m_direction * direction;
    direction *= m_speed * (m_sprinting ? 2 : 1);
    if (m_stamina > 0)
    {
        m_stamina -= 1;
    }
    else
    {
        m_sprinting = false;
    }
    incrementPosition(direction);
}

int PlayerEntity::stamina() const
{
    return m_stamina;
}

void PlayerEntity::setStamina(const int i_stamina)
{
    m_stamina = i_stamina;
}

void PlayerEntity::setColony(s_Colony* i_colony)
{
    m_colony = i_colony;
}

s_Colony* PlayerEntity::colony() const
{
    return m_colony;
}