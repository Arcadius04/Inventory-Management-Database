/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#include "Component.hpp"

Component::Component(std::string category, std::string type, int stock){
    this->category = category;
    this->type = type;
    this->stock = stock;
}
std::string Component::getCategory()
{
    return this->category;
}
std::string Component::getType()
{
    return this->type;
}
int Component::getStock()
{
    return this->stock;
}
int Component::setStock(int stock)
{
    this->stock = stock;
    return this->stock;
}
