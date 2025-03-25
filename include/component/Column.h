//
// Created by thoma on 22/03/2025.
//

#ifndef COLUMN_H
#define COLUMN_H

#include <cstdint>

class Column {
  public:
    uint8_t m_componentID;
    std::shared_ptr<void> m_column;

};

#endif //COLUMN_H
