/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#include "Library.hpp"

using namespace std;
// Ability to use the console namespace functions without calling the namespace itself
using namespace Console;

Library::Library(std::string inventoryPath)
{
    // Create a new inventory with the path inputted to the library
    Inventory inv(inventoryPath);
    // Assign the new inventory to the data member in the library
    this->inv = inv;
}
Inventory& Library::getInventory()
{
    // Return the inventory in the library
    return this->inv;
}
int Library::loginRequest()
{
    string userName;
    string userPassword;
    int loginAttempt = 0;
    int choice;
    // If the choice is not a login or exit display the options
    while(choice!=1&&choice!=2)
    {
        consolePrint("$8********************************$7Electrical Components Inventory Manager$8********************************\n");
        consolePrint("$14Choose An Option\n");
        consolePrint("1. Login\n");
        consolePrint("2. Exit Program\n");
        consolePrint("Input: ");
        cin>>choice;
        // If the input fails the input buffer is to be cleared and the any flags are ignored
        if(cin.fail())
        {
            choice = -1;
            // Clear the console input buffer
            cin.clear();
            // Ignore the inputted stream until the next line
            cin.ignore(INT_MAX,'\n');
        }
        switch(choice)
        {
        // Case 1 runs when login is requested
        case 1:
        {
            // The user will get prompted to login as long as the login attempts don't go over 3.
            while (loginAttempt < 3)
            {
                loginAttempt++;
                consolePrint("\n$8----------------[$10Login$2 "+ std::to_string(loginAttempt) + "/3$8]----------------\n");
                consolePrint("Enter User ID: ");
                cin >> userName;
                consolePrint("Enter Password: ");
                cin >> userPassword;
                // The login credentials that are allowed
                if (userName == "Yusuf" && userPassword == "YusufQ")
                {
                    consolePrint("$8-------------------------------------------\n\n");
                    consolePrint("\t Welcome "+userName+"!\n\n");
                    consolePrint("$8-------------------------------------------\n\n\n");
                    break;
                }
                else if (userName == "Muhanna" && userPassword == "MAlnoaimi")
                {
                    consolePrint("$8-------------------------------------------\n\n");
                    consolePrint("\t Welcome "+userName+"!\n\n");
                    consolePrint("$8-------------------------------------------\n\n\n");
                    break;
                }
                else
                {
                    // The login failed and it will rerun the loop since there's no break statement
                    consolePrint("\n");
                    displayErrorMessage("$12Invalid login attempt. Please try again.\n\n");
                }
                if (loginAttempt >= 3)
                {
                    // If login attempts are 3 or greater return a -1 to the caller and break out of while loop
                    displayErrorMessage("Too many login attempts!\n$12************************PROGRAM HAS BEEN TERMINATED***************************$7\n");
                    return -1;
                }
            }

            break;
        }
        // The user requested to log out
        case 2:
            consolePrint("$10****************************System Shutdown****************************$7\n");
            return 0;
        // Invalid option
        default:
            displayErrorMessage("Operation Failed: invalid option! Try again.\n");
            continue;
        }
    }
    return 1;
}

void Library::printDisplayMenu(Inventory& inv)
{
    consolePrint("$8-------------------------------------------\n");
    consolePrint("$14Choose An Operation:\n");
    consolePrint("1. Withdraw\n");
    consolePrint("2. Deposit\n");
    consolePrint("3. Display Full Inventory\n");
    consolePrint("4. Exit Program\n");
    consolePrint("Input: ");
    int inp;
    cin >> inp;

    // If the input fails the input buffer is to be cleared and the any flags are ignored
    if(cin.fail())
    {
        inp = -1;
        // Clear the console input buffer
        cin.clear();
        // Ignore the inputted stream until the next line
        cin.ignore(INT_MAX,'\n');
    }
    // Based on input switch determines which function is called.
    switch(inp)
    {
    // Case 1 runs when a withdraw operation is requested by the user
    case 1:
    {
        // Initially start the condition as a "rerun"
        int ret = printWithdrawMenu(inv);
        while(ret==-1||ret==2)
        {
            ret = printWithdrawMenu(inv);
        }
        // User requested to go back therefore rerunning this function recursively
        if(ret==0)
        {
            // Rerun this function recursively
            printDisplayMenu(inv);
        }
        if(ret==1)
        {
            // Show updated inventory
            inv.displayRemovedInventory();
            // Void this recursive function when a new recursive function is called
            //ret=-1;
            // Request if another operation is wanted
            int i = 1;
            string permission;
            do
            {
                consolePrint("$14Would you like to perform another operation? (Y/N)\n");
                consolePrint("Input: ");
                cin >> permission;
                if(permission == "Y" || permission == "y")
                {
                    // Ensure when control is back to previous function the loop is done
                    i=5;
                    printDisplayMenu(inv);
                    break;
                }
                else if(permission == "N" || permission == "n")
                {
                    // Ensure when control is back to previous function the loop is done
                    i=5;
                    displayInfoMessage("$10Thank you for using the Electrical Components Inventory Manager, have a nice day!$7\n");
                    break;
                }
                else
                {
                    displayErrorMessage("Operation Failed: (Attempt$12 " + std::to_string(i) + "/3$4 ): I did not understand \'$12 " + permission + " $4\'.\n");
                }
            }
            while(i++ < 3);
        }
        break;
    }
    case 2:
    {
        int ret = printDepositMenu(inv);
        // If the function returned a go back or an error the user will be going back
        if(ret == 0 || ret == -1)
        {
            // Prompt the user with the Operations menu
            printDisplayMenu(inv);
        }
        if(ret == 1)
        {
            // Show updated inventory
            inv.displayRemovedInventory();
            // Void this recursive function when a new recursive function is called
            ret=-1;
            // Request if another operation is wanted
            int i = 1;
            string permission;
            do
            {
                consolePrint("$14Would you like to perform another operation? (Y/N)\n");
                consolePrint("Input: ");
                cin >> permission;
                if(permission == "Y" || permission == "y")
                {
                    // Ensure when control is back to previous function the loop is done
                    i=5;
                    printDisplayMenu(inv);
                    break;
                }
                else if(permission == "N" || permission == "n")
                {
                    // Ensure when control is back to previous function the loop is done
                    i=5;
                    displayInfoMessage("$10Thank you for using the Electrical Components Inventory Manager, have a nice day!$7\n");
                    break;
                }
                else
                {
                    displayErrorMessage("Operation Failed: (Try$12 " + std::to_string(i) + "/3 $4): I did not understand \' $12" + permission + "\ $4'.\n");
                }
            }
            while(i++ < 3);
        }
        break;
    }
    //
    case 3:
    {
        inv.displayComponents();
        printDisplayMenu(inv);
        break;
    }
    // Exit program is called
    case 4:
        consolePrint("$10****************************System Shutdown****************************$7\n");
        break;
    // Invalid option
    default:
        displayErrorMessage("Operation Failed: invalid option! Try again.\n");
        printDisplayMenu(inv);
        break;
    }
}

int Library::printDepositMenu(Inventory& inv)
{
    string category;
    string type;
    string deposit;
    int d;
    // Prompt user to input a component name with a maximum attempts of 3
    int i = 1;
    while(i <= 3)
    {
        consolePrint("$8[$12 " + std::to_string(i) + "/3 $8] $14Please insert the component category/component name you would like to deposit. (Type 0 to cancel and go back)\n");
        consolePrint("Input: ");
        cin >> category;
        // Return 0 to caller in order to go previous menu
        if(category=="0")
        {
            return 0;
        }
        bool isDigit = false;
        // Checks if there's a digit in the component name for validation
        for(int k = 0; k <= category.size()-1; k++)
        {
            if(isdigit(category[k]))
            {
                displayErrorMessage("Operation Failed: You must input only letters for the component name!\n");
                isDigit = true;
                break;
            }
        }
        // If the component is not a digit
        if(!isDigit)
        {
            if(category=="")
            {
                // Category is empty skip the else code and loop
                displayErrorMessage("Operation Failed: You can't leave the category/component name empty!\n");
            }
            else
            {
                // Category is not empty and is valid break out and continue with code
                break;
            }
        }
        i++;
    }
    // If the attempts surpass 3 attempts return -1 (Leave the caller decide what to do)
    if(i > 3)
    {
        displayErrorMessage("Operation Failed: You have exhausted your attempts to deposit a component\n");
        consolePrint("$8-------------------------------------------\n");
        displayInfoMessage("$14Going back!\n");
        return -1;
    }
    // Reset the counter and prompt the user to insert component type with a maximum attempts of 3
    i=1;
    while(i <= 3)
    {
        consolePrint("$8[$12 " + std::to_string(i) + "/3 $8] $14Please insert the component type/value you would like to deposit. (Type 0 to cancel and go back)\n");
        consolePrint("Input: ");
        cin >> type;
        // Return 0 to the caller in order to go back to previous menu
        if(type == "0")
        {
            return 0;
        }
        else if(type=="")
        {
            displayErrorMessage("Operation Failed: You can't leave the type/value empty!\n");
            return -1;
        }
        else
        {
            // Type/value is valid break out of the loop and continue the code
            break;
        }
        i++;
    }
    // If the attempts surpass 3 attempts return -1 (Leave the caller decide what to do)
    if(i > 3)
    {
        displayErrorMessage("Operation Failed: You have exhausted your attempts to deposit a component\n");
        consolePrint("$8-------------------------------------------\n");
        displayInfoMessage("$14Going back!\n");
        return -1;
    }
    // Reset the counter and prompt the user to insert amount deposited with a maximum attempts of 3
    i=1;
    while(i <= 3)
    {
        consolePrint("$8[$12 " + std::to_string(i) + "/3 $8] $14Please insert amount you would like to deposit. (Type 0 to cancel and go back)\n");
        consolePrint("Input: ");
        cin >> deposit;
        // If the input fails the input buffer is to be cleared and the any flags are ignored
        if(cin.fail())
        {
            deposit = -1;
            // Clear the console input buffer
            cin.clear();
            // Ignore the inputted stream until the next line
            cin.ignore(INT_MAX,'\n');
        }
        // Return 0 to caller if user inputed 0 to go back to previous menu
        if(deposit=="0")
        {
            return 0;
        }
        bool isDigit = true;
        // Check if the string deposit contains a non-integer character
        for(int k = 0; k <= deposit.size()-1; k++)
        {
            if(!isdigit(deposit[k]))
            {
                displayErrorMessage("Operation Failed: You can only insert positive numbers for the deposit!\n");
                isDigit = false;
                break;
            }
        }
        // If previous check passed isDigit remains true and the compound statement is called
        if(isDigit)
        {
            // Converts deposit string to integer and assigns the value to d
            d = std::stoi(deposit);
            if(d<1)
            {
                consolePrint("$8[$7!$8] $4Operation Failed: You can't deposit a component less than 1 of a component!\n");
            }
            else
            {
                // The deposited value is valid break out of the loop and continue the code
                break;
            }
        }
        i++;
    }
    // If the attempts surpass 3 attempts return -1 (Leave the caller decide what to do)
    if(i > 3)
    {
        displayErrorMessage("Operation Failed: You have exhausted your attempts to deposit a component\n");
        consolePrint("$8-------------------------------------------\n");
        displayInfoMessage("$14Going back!\n");
        return -1;
    }
    // All checks were successful the following line performs the transaction
    displayInfoMessage("$10You have successfully deposited$2 " + std::to_string(d) + "$10!\n$7");
    inv.deposit(category,type,d);
    // Returning 1 indicating success
    return 1;

}

int Library::printWithdrawMenu(Inventory& inv)
{
    consolePrint("$8-------------------------------------------\n");
    consolePrint("$14Which components would you like to withdraw? (Type a number or 0 to go back)\n");
    // Create a temporary map to show the available categories to withdraw from
    std::map<int,string> avCats = inv.getAvailableCategories();
    // Check if the inventory is empty
    if(avCats.empty())
    {
        consolePrint("$7The inventory is empty! Perhaps choose the deposit operation?\n");
    }
    // Initialize an iterator assigning it the beginning and check if it doesn't point at the last element increment
    for(std::map<int,string>::iterator k = avCats.begin(); k!=avCats.end(); k++)
    {
        // Output the first (key) and the second (value)
        consolePrint(std::to_string((*k).first) + ". " + (*k).second + "\n");
    }
    consolePrint("Input: ");
    int inp;
    cin >> inp;
    // If the input fails the input buffer is to be cleared and the any flags are ignored
    if(cin.fail())
    {
        // Clear the console input buffer
        cin.clear();
        // Ignore the inputted stream until the next line
        cin.ignore(INT_MAX,'\n');
        displayErrorMessage("Operation Failed: You can only insert positive numbers for the input!\n");
        return -1;
    }
    // Return 0 for the caller to prompt the user with the previous menu
    if(inp==0)
    {
        consolePrint("$8-------------------------------------------\n");
        displayInfoMessage("$14Going back!\n");
        return 0;
    }
    consolePrint("$8-------------------------------------------\n");
    // The inputted value is matched to the key in the map using the operation find
    auto finding = avCats.find(inp);
    // When operation fails it will point to the last element
    if(finding==avCats.end())
    {
        displayErrorMessage("Operation Failed: Inputted value '$12 " + std::to_string(inp) + " $4' is not attached to any component!\n");
        return -1;
    }
    // Initialize chosenCat and assign the string to the value which is the name of the category selected from input
    string chosenCat = finding->second;
    consolePrint("You have chosen: $2" + chosenCat + "\n");
    // Allow user to reattempt withdrawing the same category using a while loop
    while(true)
    {
        consolePrint("$14Please select the value you would like to withdraw (Type a number or 0 to go back): \n");
        // Fetch a vector of components available if each component matches the category used in the parameter
        std::vector<Component> available = inv.getComponentsFromCategory(chosenCat);
        // Create a temporary map of the available components by attaching them to a key for user to use as an input
        std::map<int, string> avComp;
        // Print out all the components and at the same time populate the map
        for(int i = 0; i < available.size(); i++)
        {
            consolePrint(""
                         + std::to_string(i+1)
                         + ". " + available[i].getType()
                         + ", $10(Available:"
                         + std::to_string(available[i].getStock())
                         + ")\n");
            avComp[i]=available[i].getType();
        }
        consolePrint("Input: ");
        int compinp;
        cin>>compinp;
        // If the input fails the input buffer is to be cleared and the any flags are ignored
        if(cin.fail())
        {
            // Clear the console input buffer
            cin.clear();
            // Ignore the inputted stream until the next line
            cin.ignore(INT_MAX,'\n');
            displayErrorMessage("Operation Failed: You can only insert positive numbers for the input!\n");
            continue;
        }
        // Return 2 to the caller to indicate the need to rerun the withdraw menu
        if(compinp==0)
        {
            consolePrint("$8-------------------------------------------\n");
            displayInfoMessage("$14Going back!\n");
            return 2;
        }
        consolePrint("$8-------------------------------------------\n");
        auto compFinding = avComp.find(compinp-1);
        if(compFinding==avComp.end())
        {
            displayErrorMessage("$4Operation Failed: Inputted value '$12 " + std::to_string(compinp) + " $4' is not attached to any component value!\n");
            continue;
        }
        // Create a dummy returned object that will exit the while loop if the returned object is valid and not a nothing object
        Component ret("","",-1);
        while(ret.getStock()==-1)
        {
            string chosenType = compFinding->second;
            Component comp = inv.getComponent(chosenCat,chosenType);
            consolePrint("You have chosen: $2" + chosenCat + " > " + chosenType + " $10(Available:" + std::to_string(comp.getStock()) + ")\n");
            consolePrint("$14Please enter amount you want to withdraw. (Type 0 to go back to select another component)\n");
            consolePrint("Input: ");
            int withdraw;
            cin>>withdraw;
            // If the input fails the input buffer is to be cleared and the any flags are ignored
            if(cin.fail())
            {
                // Clear the console input buffer
                cin.clear();
                // Ignore the inputted stream until the next line
                cin.ignore(INT_MAX,'\n');
                displayErrorMessage("Operation Failed: Bad input! Must be an integer and not over the range \'" + std::to_string(INT_MAX) + "\'.\n");
                continue;
            }
            if(withdraw==0)
            {
                //rerun withdraw
                consolePrint("$8-------------------------------------------\n");
                displayInfoMessage("$14Going back!\n");
                return 2;
            }
            else if(withdraw < 0)
            {
                displayErrorMessage("Operation failed: You can only withdraw more than or equal to 1!\n");
                consolePrint("$8-------------------------------------------\n");
                // Ask to input a withdraw value again
                continue;
            }
            else if(comp.getStock() < withdraw)
            {
                displayErrorMessage("Operation failed: Stock available:$12 " + std::to_string(comp.getStock()) + "\n");
                consolePrint("$8-------------------------------------------\n");
                // Ask to input a withdraw value again
                continue;
            }
            consolePrint("$8-------------------------------------------\n");
            ret = inv.withdraw(chosenCat,chosenType,withdraw);
            if(ret.getStock() != -1 && ret.getStock() != 0)
            {
                displayInfoMessage("$10You have successfully withdrawn$2 " + std::to_string(withdraw) + "$10!\n$7");
                return 1;
            }
        }
    }
    return 1;
}
