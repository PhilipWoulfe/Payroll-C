/**
* CompanyPayroll
*
* FIT ICTAP Procedural Programming Assignment
*
* Author Philip Woulfe
* Version 1.0
* 2016-10-05
* Header for creation of UI
*/

#ifndef __Payroll_h__
#define __Payroll_h__

// used to underline text for UI 
#define ANSI_UNDERLINED_PRE  "\033[4m"
#define ANSI_UNDERLINED_POST "\033[0m"

#include <stdio.h>
#include <windows.h>

#include "Employee.h"

/* Display Header */
void displayHeader(void);

/* Clear command screen */
void clearScreen(void);

/* Load text with character delay */
void printText(char *text);

/* Display main menu */
void displayMenu(void);

/* Display Employees */
void displayEmployees(Employee_t employees[], int arrayLength);

#endif /* __Payroll_h_ */