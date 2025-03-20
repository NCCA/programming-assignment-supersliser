//
// Created by tom on 3/20/25.
//

#ifndef MOVEABLEENTITY_H
#define MOVEABLEENTITY_H
#include <ngl/Vec3.h>
#include <ngl/Quaternion.h>
#include "ObjectEntity.h"

class a_MoveableEntity : public a_ObjectEntity
{
    protected:
    ngl::Vec3 m_direction = ngl::Vec3(0.0f, 0.0f, 1.0f);
    int m_speed = 1;
    int m_health = 100;
    int m_maxHealth = 100;
public:
    virtual void setDirection(const ngl::Vec3& i_direction);
    virtual void rotate(const ngl::Vec3 i_axis, const int i_rotation);
    virtual ngl::Vec3 direction() const;
    virtual void setSpeed(const int i_speed);
    virtual int speed() const;
    virtual void damage(const int i_damage);
    virtual void heal(const int i_healing);
    virtual int health() const;
    a_MoveableEntity() = default;
    a_MoveableEntity(ngl::Vec3 i_position, ngl::Vec3 i_direction = ngl::Vec3(0.0f, 0.0f, 1.0f), int i_health = 100, int i_speed = 1, bool i_visible = true, bool i_selectable = false);
    virtual ~a_MoveableEntity() = default;

};

#endif //MOVEABLEENTITY_H
