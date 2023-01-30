/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#ifndef _Library_HPP_
#define _Library_HPP_
#include "Inventory.hpp"
#include "Console.hpp"
#include <string>
#include <iostream>
// Allows access to max and min integer range
#include <limits.h>

class Library
{
private:
    // Inventory object stored in memory
    Inventory inv;

public:
    Library(std::string inventoryPath);
    /**
     * Allow getting the inventory through the library
     *
     * @return the inventory
     */
    Inventory& getInventory();
    /**
    * A call to prompt the user to login
    * @return -1 (Unsuccessful login)
    *          0 (Exit is called)
    *          1 (Successful login)
    */
    int loginRequest();
    /**
     * Prompts user to select the action (withdraw, deposit, exit, display inventory)
     * Main caller to other functions recursively based on what each function returns.
     *
     * @param inv inventory is passed by reference (Any changes will be made without making copies of passed inv)
     * @return void
     */
    void printDisplayMenu(Inventory& inv);
    /**
     *   Prompts the user with withdraw options and has an ability
     *   to recursively runs, the options are embedded inside the function.
     *
     *   @param inv inventory is passed by reference (Any changes will be made without making copies of passed inv)
     *   @return int -1 error and has to rerun
     *                0 prompts previous menu
     *                1 completes function no need to run again
     *                Any other return will rerun function
     *
     */
    int printWithdrawMenu(Inventory& inv);
    /**
     *   Prompts the user with deposit options and has an ability
     *
     *   @param inv inventory is passed by reference (Any changes will be made without making copies of passed inv)
     *   @return int -1 error leaving the caller the choice with what to do
     *                0 prompts previous menu
     *                1 completes function no need to run again
     *                Any other return will rerun function
     *
     */
    int printDepositMenu(Inventory& inv);



};

#endif // _Library_HPP_
