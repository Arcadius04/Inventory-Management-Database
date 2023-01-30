/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#include <iostream>
#include "Library.hpp"

using namespace std;

int start()
{
    // Initialize the library object with all functions using the inventory path
    Library lib("inv.json");
    // Prompt login
    int loginReturn = lib.loginRequest();
    // -1 = Failed
    // 0 = Logout
    // 1 = Success Proceed
    if(loginReturn==-1)
    {
        // User failed to login and the process is terminated here
        return -1;
    }
    else if(loginReturn == 0)
    {
        // User asked to logout and it returned an integer that doesn't indicate failure
        return 0;
    }
    // After login is sucessful user is prompted with operations
    lib.printDisplayMenu(lib.getInventory());
    return 0;
}

int main()
{
    // Perform the start function and return to the operating system
    return start();
}
