//
// Created by tom on 3/20/25.
//

#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include "Camera.h"
#include "Colony.h"
#include "MoveableEntity.h"


class PlayerEntity : public a_MoveableEntity
{
    protected:
    Camera m_camera;
    bool m_sprinting = false;
    int m_stamina = 100;
    s_Colony* m_colony;
    public:
    PlayerEntity() = default;
    PlayerEntity(ngl::Vec3 i_position, ngl::Vec3 i_direction, int i_health);
    void startSprint();
    void stopSprint();
    void move(const ngl::Vec2& i_direction);
    int stamina() const;
    void setStamina(int i_stamina);
    void setColony(s_Colony* i_colony);
    s_Colony* colony() const;
    ~PlayerEntity() = default;

};

#endif //PLAYERENTITY_H
