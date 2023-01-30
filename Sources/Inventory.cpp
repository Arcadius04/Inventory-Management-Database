/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#include "Headers/Inventory.hpp"

using namespace Console;

Inventory::Inventory()
{
}
Inventory::Inventory(std::string location)
{
    // The file location
    this->location = location;
    // Create input file stream object
    std::ifstream file(location);
    // If file doesn't exist (It failed to read it)
    if(file.fail())
    {
        // Create empty file
        std::ofstream outputFile(location);

    }
    // Attempt to parse the JSON file and if it fails ignore it since the inventory checks for empty file
    try
    {
        json data = json::parse(file);
        // Loop through each categories in the inventory object JSON
        for(auto category : data["Inventory"].items())
        {
            // Loop through each type in the inventory.category object JSON
            for(auto type : category.value().items())
            {
                // Go through every object in the JSON file and deposit it in memory
                deposit((std::string)category.key(), (std::string)type.key(),(int)type.value());
            }
        }
    }
    catch(std::exception e)
    {
        //ignore already checks for empty inventory
    }
}
Inventory::~Inventory()
{
    // Create an output stream object and set its path to the location of the inventory
    std::ofstream o(this->location);
    // Create a JSON object and parse all the components in memory into it
    json data;
    int componentsInMemory = 0;
    // Loop through all components in memory
    for(Component& c : getComponents())
    {
        componentsInMemory++;
        // The data variable acts like a nested array
        data["Inventory"][c.getCategory()][c.getType()] = c.getStock();
    }
    // If there's components in memory allow writing to file (avoids overwriting empty file)
    if(componentsInMemory>0)
    {
        // Parse the data into the output file
        o << data << std::endl;
    }
}
std::vector<Component>& Inventory::getComponents()
{
    // Return the components vector in the inventory object
    return this->components;
}
Component& Inventory::withdraw(std::string category, std::string type, int withdraw)
{
    // Loop for each component in the inventory
    for(Component& c : getComponents())
    {
        // If the component is found based on the parameters of the function
        if(category==c.getCategory()&&type==c.getType())
        {
            // Check if the withdrawn amount is greater than the stock
            int stock = c.getStock();
            if(stock < withdraw)
            {
                // Return a dummy component with -1 stock for the process to handle
                Component noStock("","",-1);
                return noStock;
            }
            else
            {
                // Otherwise subtract from the stock and update it to the component
                c.setStock(stock-withdraw);
            }
            // Return the component itself
            return c;
        }
    }
    // Return a dummy component called nothing
    Component nothing("","",0);
    return nothing;
}
Component& Inventory::deposit(std::string category, std::string type, int deposit)
{
    // If the category inputted to the parameter is nothing return a dummy component
    if(category=="")
    {
        displayErrorMessage("Operation Failed: Category can't be empty!\n");
        Component nothing("","",0);
        return nothing;
    }
    // If the type inputted to the parameter is nothing return a dummy component
    if(type=="")
    {
        displayErrorMessage("Operation Failed: Type can't be empty!\n");
        Component nothing("","",0);
        return nothing;
    }
    // If the deposit inputted to the parameter is less than or equal to 0 return a dummy component
    if(deposit<=0)
    {
        displayErrorMessage("Operation Failed: Deposited amount can't be less than 1!\n");
        Component nothing("","",0);
        return nothing;
    }
    // Loop through all available components
    for(Component& c : getComponents())
    {
        // If the category and type inputted matches any of the components already in
        if(category==c.getCategory()&&type==c.getType())
        {
            // Add to the stock
            int stock = c.getStock();
            c.setStock(stock+deposit);
            // return the component
            return c;
        }
    }
    // Create a new component with the same category type and deposited stock
    Component comp(category,type,deposit);
    // Add the new component to the vector of the components in the inventory
    getComponents().push_back(comp);
    // Return the new component
    return comp;
}
std::map<int,std::string> Inventory::getAvailableCategories()
{
    // Create a temporary map of the categories available
    std::map<int,std::string> categories;
    // Start the key value from 1
    int i = 1;
    // For each component loop to add a new category to the map
    for(Component& c : getComponents())
    {
        // The variable starts by default as false the category of the component isn't in the map
        bool inAlready = false;
        // Iterator through the temporary category map to check if the component's category is in the loop
        for(std::map<int,std::string>::iterator k = categories.begin(); k != categories.end(); k++)
        {
            // k.second represents the value in the map attached to the key
            if((*k).second==c.getCategory())
            {
                // Set already in true
                inAlready = true;
            }
        }
        // if it's not already in
        if(inAlready==false)
        {
            // Increment after using 'i' and input the category to the map
            categories[i++] = c.getCategory();
        }
    }
    // Return the available categories
    return categories;
}
std::vector<Component> Inventory::getComponentsFromCategory(std::string category)
{
    // Create a temporary component vectors
    std::vector<Component> components;
    // Loop through all components in vector
    for(Component& c : getComponents())
    {
        // If components in the vector match the category from the parameter
        if(c.getCategory() == category)
        {
            // Push back to the end of the stack of the temporary component vector
            components.push_back(c);
        }
    }
    return components;
}

Component& Inventory::getComponent(std::string category, std::string type)
{
    // Loop through all the components in the vector
    for(Component& c : getComponents())
    {
        // Check for each component iteration if the category and type matches the parameter inputted
        if(category==c.getCategory()&&type==c.getType())
        {
            return c;
        }
    }
    Component nothing("","",0);
    return nothing;
}

void Inventory::displayComponents()
{
    consolePrint("$8----------------[$10Inventory$8]----------------\n");
    int numOfComponents = 0;
    // Loop through all components in the vector
    for(Component& c : getComponents())
    {
        numOfComponents++;
        // Print in the output stream the component information stored in the object
        consolePrint("Component: " + c.getCategory() + ", " + "Value: " + c.getType() + " $2(Available: " + std::to_string(c.getStock())+")\n");
    }
    // If no components were found in the inventory
    if(numOfComponents==0)
    {
        consolePrint("$7The inventory is empty! Perhaps choose the deposit operation?\n");
    }
    consolePrint("$8-------------------------------------------\n");
}

void Inventory::displayRemovedInventory()
{
    consolePrint("$8----------------[$10Updated Inventory$8]----------------\n");
    int numOfComponents = 0;
    // Loop through all components in the vector
    for(Component& c : getComponents())
    {
        numOfComponents++;
        // Print in the output stream the component information stored in the object
        consolePrint("Component: " + c.getCategory() + ", " + "Value: " + c.getType() + " $2(Available: " + std::to_string(c.getStock())+")\n");
    }
    // If no components were found in the inventory
    if(numOfComponents==0)
    {
        consolePrint("$7The inventory is empty! Perhaps choose the deposit operation?\n");
    }
    consolePrint("$8-------------------------------------------\n");
}
