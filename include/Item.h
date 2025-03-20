//
// Created by s5605187 on 20/03/25.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>

#include "e_item.h"

class a_Item
{
protected:
    e_item m_item = e_item::NULL_ITEM;
public:
    virtual void use() = 0;
    virtual std::string name();
    virtual ~a_Item() = default;
};

#endif //ITEM_H
