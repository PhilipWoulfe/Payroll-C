/**
* CompanyPayroll
*
* FIT ICTAP Procedural Programming Assignment
*
* Author Philip Woulfe
* Version 1.0
* 2016-10-05
* Body for creation of Employee Data type
*/

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <windows.h>

#include "Employee.h"

/* Load employee record */
int loadEmployees(Employee_t employees_p[], int arrayLength) {

	printText("Loading employee records...\n");

	// remember filenames
	char *infile = "EmployeeList.csv";

	// open input file
	FILE* inptr = fopen(infile, "r");
	if (inptr == NULL)
	{
		/* Create message string */
		char *message = "Could not open ";
		char *messageFull = malloc(strlen(message) + 1 + strlen(infile) + "...\n");
		strcpy(messageFull, message);
		strcat(messageFull, infile);
		strcat(messageFull, "...\n");

		printText(messageFull);

		printText("Creating File...\n");
		Sleep(2000);

		inptr = fopen(infile, "w");

		printText("File Created...\n");

		// free memory
		free(messageFull);
	}
	else {
		printText("Employee records loaded...\n");
	}

	char line[50];
	arrayLength = 0;

	while (fgets(line, 50, inptr))
	{
		char* tmp = _strdup(line);
		//if (employee_p[count] != NULL) {
		strcpy(employees_p[arrayLength].name, getfield(tmp, 1));
		employees_p[arrayLength].dept = atoi(getfield(_strdup(line), 2));
		employees_p[arrayLength].rate = atoi(getfield(_strdup(line), 3));
		employees_p[arrayLength].currentEmployee = atoi(getfield(_strdup(line), 4));
		//printf(employees_p[count].name);

		arrayLength++;
		//printf("Field 3 would be %s\n", getfield(tmp, 1));
		//}

		// NOTE strtok clobbers tmp
		free(tmp);
	}
	//printf("Test");
	// close infile
	fclose(inptr);

	return arrayLength;
}

const char* getfield(char* line, int num)
{

	const char* tok;
	for (tok = strtok(line, ",");
		tok && *tok;
		tok = strtok(NULL, ",\n"))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}
