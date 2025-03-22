//
// Created by s5605187 on 22/03/25.
//

#include "Table.h"

#include "component/Entity.h"
#include "component/PositionComponent.h"

uint32_t Table::createEntity() {
    if (m_columns.empty()) {
        Entity* ColumnItem = new Entity();
        ColumnItem->addEntity();
        m_columns.push_back({ColumnItem->getComponentID(), ColumnItem});
        return 0;
    }
    static_cast<Entity*>(m_columns[0].m_column)->addEntity();
    for (size_t i = 1; i < m_columns.size(); i++) {
        switch (m_columns[i].m_componentID)
        {
            case 1:
                static_cast<Entity*>(m_columns[i].m_column)->addEntity();
        case 2:
            static_cast<PositonComponent*>(m_columns[i].m_column)->m_ps.push_back(ngl::Vec3());
        }
    }
    return static_cast<Entity*>(m_columns[0].m_column)->getEntityCount() - 1;
}

uint32_t Table::registerComponentType(const uint8_t i_componentType) {
    for (size_t i = 0; i < m_columns.size(); i++) {
        if (m_columns[i].m_componentID == i_componentType) {
            return 0;
        }
    }
    switch (i_componentType)
    {
        case 1:
            m_columns.push_back({i_componentType, new Entity()});
            break;
        case 2:
            m_columns.push_back({i_componentType, new PositonComponent(static_cast<Entity*>(m_columns[0].m_column)->getEntityCount())});
            break;
    }
    return m_columns.size() - 1;
}

std::vector<Column> Table::getEntity(uint32_t i_entity) const {
    std::vector<Column> entity;
    for (size_t i = 0; i < m_columns.size(); i++) {
        switch (m_columns[i].m_componentID)
        {
            case 1:
                entity.push_back(m_columns[i]);
                break;
            case 2:
                entity.push_back(m_columns[i]);
                break;
        }
    }
    return entity;
}

int Table::getComponentIndex(uint8_t i_componentType) const
{
    for (size_t i = 0; i < m_columns.size(); i++) {
        if (m_columns[i].m_componentID == i_componentType) {
            return i;
        }
    }
    return -1;
}