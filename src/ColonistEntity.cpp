//
// Created by s5605187 on 20/03/25.
//

#include "ColonistEntity.h"

void ColonistEntity::hire(const e_job i_job)
{
    m_job = i_job;
}

void ColonistEntity::fire()
{
    m_job = e_job::UNEMPLOYED;
}

e_job ColonistEntity::job() const
{
    return m_job;
}

void ColonistEntity::setColony(s_Colony* i_colony)
{
    m_colony = i_colony;
}

s_Colony* ColonistEntity::colony()
{
    return m_colony;
}

ColonistEntity::ColonistEntity(const e_job i_job)
{
    m_job = i_job;
    m_maxHealth = 100;
    m_speed = 1;
    m_visible = true;
    m_selectable = false;
    m_selected = false;
    m_position = ngl::Vec3(0.0f, 0.0f, 0.0f);
    m_direction = ngl::Vec3(0.0f, 0.0f, 1.0f);
    m_colony = nullptr;
}

ColonistEntity::ColonistEntity(const ngl::Vec3 i_position, const ngl::Vec3 i_direction, const e_job i_job)
{
    m_position = i_position;
    m_direction = i_direction;
    m_job = i_job;
    m_maxHealth = 100;
    m_speed = 1;
    m_visible = true;
    m_selectable = false;
    m_selected = false;
    m_colony = nullptr;
}

void ColonistEntity::move(ngl::Vec2 i_direction)
{
    auto direction = getMovementVector(i_direction);
    direction *= m_speed;
    incrementPosition(direction);
}