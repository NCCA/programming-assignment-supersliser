//
// Created by s5605187 on 22/03/25.
//

#include "Table.h"
#include "component/BlockComponents.h"
#include "component/CameraComponents.h"
#include "component/Entities.h"
#include "component/TransformComponents.h"
#include "component/BlockTextureComponent.h"
#include "Camera.h"
#include "component/IsSprintingComponent.h"
#include "component/SpeedComponent.h"
#include "system/ApplyBlockTextureSystem.h"

uint32_t Table::createEntity()
{
    if (m_columns.empty())
    {
        std::shared_ptr<Entities> ColumnItem = std::make_shared<Entities>();
        ColumnItem->addEntity();
        m_columns.push_back({Entities::getComponentID(), (std::move(ColumnItem))});
        return 0;
    }
    for (size_t i = 0; i < m_columns.size(); i++)
    {
        switch (m_columns[i].m_componentID)
        {
        case 1:
            static_cast<Entities*>(m_columns[i].m_column.get())->addEntity();
            break;
        case 2:
            static_cast<TransformComponents*>(m_columns[i].m_column.get())->addEntity();
            break;
        case 3:
            // add anything to block component if needed
            break;
        case 4:
            {
                auto c = Camera();
                c.setDefaultCamera();
                static_cast<CameraComponents*>(m_columns[i].m_column.get())->m_cameras.push_back(c);
            }
            break;
        case 5:
            {
                static_cast<BlockTextureComponent*>(m_columns[i].m_column.get())->addBlock();
            }
            break;
        case 6:
            static_cast<IsSprintingComponent*>(m_columns[i].m_column.get())->m_isSprinting.push_back(false);
            break;
        case 7:
            static_cast<SpeedComponent*>(m_columns[i].m_column.get())->m_speed.push_back(
                SpeedComponent::getDefaultSpeed());
        }
    }
    return static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount() - 1;
}

uint32_t Table::registerComponentType(const uint8_t i_componentType)
{
    for (size_t i = 0; i < m_columns.size(); i++)
    {
        if (m_columns[i].m_componentID == i_componentType)
        {
            return 0;
        }
    }
    switch (i_componentType)
    {
    case 1:
        m_columns.push_back({i_componentType, std::make_shared<Entities>(Entities())});
        break;
    case 2:
        m_columns.push_back({
            i_componentType,
            std::make_shared<TransformComponents>(static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount())
        });
        break;
    case 3:
        m_columns.push_back({
            i_componentType,
            std::make_shared<BlockComponents>(static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount())
        });
        break;
    case 4:
        m_columns.push_back({
            i_componentType,
            std::make_shared<CameraComponents>(static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount())
        });
        break;
    case 5:
        m_columns.push_back({
            i_componentType,
            std::make_shared<BlockTextureComponent>(
                static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount())
        });
        break;
    case 6:
        m_columns.push_back({
            i_componentType,
            std::make_shared<IsSprintingComponent>(
                static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount())
        });
        break;
    case 7:
        m_columns.push_back({
            i_componentType,
            std::make_shared<SpeedComponent>(
                static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount())
        });
        break;
    }
    return m_columns.size() - 1;
}

int Table::getComponentIndex(uint8_t i_componentType) const
{
    for (size_t i = 0; i < m_columns.size(); i++)
    {
        if (m_columns[i].m_componentID == i_componentType)
        {
            return i;
        }
    }
    return -1;
}

std::shared_ptr<void> Table::getColumn(uint32_t i_columnIndex) const
{
    return m_columns[i_columnIndex].m_column;
}

Table::~Table()
{
    for (size_t i = 0; i < m_columns.size(); i++)
    {
        m_columns[i].m_column.reset();
    }
    m_columns.clear();
}

unsigned int Table::getComponentCount() const
{
    return m_columns.size();
}

unsigned int Table::getEntityCount() const
{
    return static_cast<Entities*>(m_columns[0].m_column.get())->getEntityCount();
}