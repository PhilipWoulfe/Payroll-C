/**
* CompanyPayroll
*
* FIT ICTAP Procedural Programming Assignment
*
* Author Philip Woulfe
* Version 1.0
* 2016-10-05
* Header for IO
*/

#ifndef __IO_h__
#define __IO_h__

#include <stdio.h>
#include <windows.h>

#include "Employee.h"

/* Load Employees */
int loadEmployees(Employee_t employees[], int arrayLength);

/* Get fields from csv */
const char* getfield(char* line, int num);

/* Save current employees to file */
void saveEmployeesToFile(Employee_t empArr[], int arrayLength);

#endif /* __IO_h_ */