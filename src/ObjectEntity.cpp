//
// Created by tom on 3/20/25.
//
#include "ObjectEntity.h"

void a_ObjectEntity::setPosition(const ngl::Vec3& i_position)
{
    m_position = i_position;
}

void a_ObjectEntity::incrementPosition(const ngl::Vec3& i_increment)
{
    m_position += i_increment;
}

void a_ObjectEntity::incrementPosition(const ngl::Vec3& i_direction, const int i_increment)
{
    m_position += i_direction * i_increment;
}

void a_ObjectEntity::setVisible(const bool i_visible)
{
    m_visible = i_visible;
}

bool a_ObjectEntity::visible() const
{
    return m_visible;
}

void a_ObjectEntity::setSelectable(const bool i_selectable)
{
    m_selectable = i_selectable;
}

bool a_ObjectEntity::selected() const
{
    return m_selected;
}

void a_ObjectEntity::select()
{
    m_selected = true && m_selectable;
}

void a_ObjectEntity::deselect()
{
    m_selected = false;
}

ngl::Vec3 a_ObjectEntity::position() const
{
    return m_position;
}

a_ObjectEntity::a_ObjectEntity(ngl::Vec3 i_position, bool i_visible, bool i_selectable)
{
    m_position = i_position;
    m_visible = i_visible;
    m_selectable = i_selectable;
    m_selected = false;
}
