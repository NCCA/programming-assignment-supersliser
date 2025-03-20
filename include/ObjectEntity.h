//
// Created by tom on 3/20/25.
//

#ifndef OBJECTENTITY_H
#define OBJECTENTITY_H
#include <ngl/Vec3.h>

class a_ObjectEntity
{
protected:
    ngl::Vec3 m_position = ngl::Vec3(0.0f, 0.0f, 0.0f);
    bool m_visible = true;
    bool m_selectable = true;
    bool m_selected = false;
public:
    virtual void setPosition(const ngl::Vec3& i_position);
    virtual void incrementPosition(const ngl::Vec3& i_increment);
    virtual void incrementPosition(const ngl::Vec3& i_direction, const int i_increment);
    virtual void setVisible(bool i_visible);
    [[nodiscard]] virtual bool visible() const;
    virtual void setSelectable(bool i_selectable);
    [[nodiscard]] virtual bool selected() const;
    virtual void select();
    virtual void deselect();
    [[nodiscard]] virtual ngl::Vec3 position() const;
    a_ObjectEntity() = default;
    a_ObjectEntity(ngl::Vec3 i_position, bool i_visible = true, bool i_selectable = true);
    virtual ~a_ObjectEntity() = default;
};

#endif //OBJECTENTITY_H
