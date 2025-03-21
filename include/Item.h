//
// Created by s5605187 on 20/03/25.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>

class a_Item
{
protected:
    std::string m_name = "NULL_ITEM";
    unsigned int m_id = 0;
public:
    virtual void use();
    virtual std::string name();
    virtual ~a_Item() = default;
    a_Item() = default;
    a_Item(const std::string& i_name, const unsigned int i_id);
};

#endif //ITEM_H
