/*
 * Electrical Components Inventory Manager
 *
 * Authored by:
 * Muhanna AlNoaimi / 202000153
 */

#ifndef _Console_HPP_
#define _Console_HPP_
#include <string>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

namespace Console
{
/**
*  Print strings to console with support to color coding (Symbol is set '$'), Color range 1-255
*
*  @param info is a string that will be outputted to the screen
*  @return void
*/
void consolePrint(std::string message);
/**
* Display a message with a warn prefix
*
* @param string of the error message
*
*/
void displayWarnMessage(std::string message);
/**
* Display a message with an error prefix
*
* @param string of the error message
*
*/
void displayErrorMessage(std::string message);
/**
 * Display a message with an info prefix
 *
 * @param string of the error message
 *
*/
void displayInfoMessage(std::string message);

}


#endif // _Console_HPP_
