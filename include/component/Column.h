//
// Created by thoma on 22/03/2025.
//

#ifndef COLUMN_H
#define COLUMN_H

#include <cstdint>

/// @class Column include/component/Column.h
/// @brief Utility Class to define a generic column
/// @author Thomas Lower
/// @version 1.0
/// @date 2025-03-22
class Column {
  public:
    /// @brief ID of the component stored in this column
    uint8_t m_componentID;
    /// @brief Pointer to an abstract component
    std::shared_ptr<void> m_column;

};

#endif //COLUMN_H
