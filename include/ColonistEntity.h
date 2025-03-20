//
// Created by s5605187 on 20/03/25.
//

#ifndef COLONISTENTITY_H
#define COLONISTENTITY_H
#include <ngl/Vec3.h>

#include "Colony.h"
#include "e_job.h"
#include "MoveableEntity.h"

class ColonistEntity : public a_MoveableEntity
{
protected:
    s_Colony* m_colony;
    e_job m_job = e_job::UNEMPLOYED;
public:
    void hire(const e_job i_job);
    void fire();
    e_job job() const;
    void setColony(s_Colony* i_colony);
    s_Colony* colony();
    ColonistEntity() = default;
    ~ColonistEntity() = default;
    ColonistEntity(const e_job i_job);
    ColonistEntity(const ngl::Vec3 i_position, const ngl::Vec3 i_direction, const e_job i_job);
    void move(ngl::Vec2 i_direction);
};

#endif //COLONISTENTITY_H
