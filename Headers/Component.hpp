/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#ifndef _Component_HPP_
#define _Component_HPP_
#include <string>

class Component {

private:
    // Category name of the component stored in the component object
    std::string category;
    // Type name of the component stored in the component object
    std::string type;
    // Integer of the stock available stored in the component object
    int stock;

public:
    /**
    * Constructor of the component to initialize and assign the values to the member variables
    *
    * @param category of the component or alternatively its name, type is the value of the component eg. 10k, stock is the amount available
    * @return reference of component when it is found, returns an empty component when it is not found or empty with -1 in stock if it is out of stock
    */
    Component(std::string category, std::string type, int stock);
    /**
    * Getter function to get the category of the component object
    *
    * @return string name of the category
    */
    std::string getCategory();
    /**
    * Getter function to get the type of the component object
    *
    * @return string name of the type
    */
    std::string getType();
    /**
    * Getter function to get the stock available of the component object
    *
    * @return int stock available of the component
    */
    int getStock();
    /**
    * Setter function to set the stock of the component object
    *
    * @param int stock amount (overrides the previous value)
    * @return int of the new stock value
    */
    int setStock(int stock);

};

#endif // _Component_HPP_
