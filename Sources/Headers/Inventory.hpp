/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#ifndef _Inventory_HPP_
#define _Inventory_HPP_
#include <vector>
#include <map>
#include <string>
#include "nlohmann/json.hpp"
#include "Component.hpp"
#include <iostream>
#include <fstream>
#include "Console.hpp"

class Inventory
{

// Allows to simply use json to access the ordered_json namespace
    using json = nlohmann::ordered_json;

private:
    // Vector list of all the components in the inventory stored in memory
    std::vector<Component> components;
    // Memory location of the path of the inventory
    std::string location;

public:
    /**
    * Dummy constructor to allow the library to declare without initializing
    */
    Inventory();
    /**
    * Constructor called during the initialization phase. Performs all necessary loading to memory in order
    * to ease the processing of all components in inventory.
    *
    * @param string the location path of a JSON file in the right format
    */
    Inventory(std::string location);
    /**
    * Deconstructor called when the object goes out of scope. Performs all necessary saving to the JSON file.
    */
    ~Inventory();
    /**
    * Gets all the components saved in the components vector
    *
    * @return reference of the vector of components in the inventory object
    */
    std::vector<Component>& getComponents();
    /**
    * Performs a withdraw operation from the components vector in the inventory object
    *
    * @param category of the component or alternatively its name, type is the value of the component eg. 10k, withdraw is the amount to be withdrawn
    * @return reference of component when it is found, returns an empty component when it is not found or empty with -1 in stock if it is out of stock
    */
    Component& withdraw(std::string category, std::string type, int withdraw);
    /**
    * Performs a deposit operation to the components vector in the inventory object
    *
    * @param category of the component or alternatively its name, type is the value of the component eg. 10k, deposit is the amount to be deposited
    * @return reference of component when it is found, returns an empty component when it is not found or empty with -1 in stock if it is out of stock
    */
    Component& deposit(std::string category, std::string type, int deposit);
    /**
    * Return a component from the vector list of the inventory object
    *
    * @param category or the name in string, and the type is the value of the component in string
    * @return reference of component when it is found, returns an empty component deposit failed
    */
    Component& getComponent(std::string category, std::string type);
    /**
    * Prompt the user with all the stock regardless of category or types
    */
    void displayComponents();
    /**
    * Prompt the user with all the updated stock regardless of category or types
    */
    void displayRemovedInventory();
    /**
    * Find all categories/component names stored in the components list
    *
    * @return mapped categories (in order) with each category linked to a key starting from 1
    */
    std::map<int,std::string> getAvailableCategories();
    /**
    * Return a temporary list of components based on category/component name
    *
    * @param category or the name in string, and the type is the value of the component in string
    * @return reference of each component when it is found, returns an empty vector when there are no components
    */
    std::vector<Component> getComponentsFromCategory(std::string category);



};


#endif
