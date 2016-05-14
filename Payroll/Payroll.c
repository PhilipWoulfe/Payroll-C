/**
* CompanyPayroll
*
* FIT ICTAP Procedural Programming Assignment
*
* Author Philip Woulfe
* Version 1.0
* 2016-10-05
* Create a program to calculate company payroll
*/

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "Payroll.h"
#include "Employee.h"
#include "PayrollUI.h"

/* Get Week End Date */
char * getWEDate();

int main(int argc, char* argv[])
{
	// ensure proper usage
	if (argc != 1)
	{
		printf("Usage: ./payroll (No arguments)\n");
		return 1;
	}

	// declare variables
	char input = 0;

	Employee_t employees[50];
	if (NULL == employees) {
		fprintf(stderr, "malloc failed\n");
		return(-1);
	}
	int arrayLength = 0;
	/*int len = 0;
	arrayLength = &len;
	*/

	// Resize command window
	system("MODE 85,50");

	displayHeader();
	arrayLength = loadEmployees(employees, arrayLength);
	/*arrayLength = &i;
	printf(employees[0].name);
	printf(arrayLength);
	getchar();*/

	//printf((*employees_p[0]).name);
	// loop through menu until quit
	do {

		displayMenu();

		// Loop until valid input
		do {

			input = getch();

			switch (input) {
				case '1':
					displayEmployees(employees, arrayLength);
					break;
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
					processWages(employees, arrayLength);
				case '7':
					break;

				default:
					printText("  Invalid selection...");
					printText("  Please select an option from the menu [1-7]: ");

			}

		} while (input < '1' || input > '7');

	} while (input != '7');

	//processWages();

	printText("Exiting program...\n");

	// that's all folks
	return 0;
}





/* Processes wages for employees and save to file */
void processWages(Employee_t empArr[], int arrayLength) { //TODO reimplement
//void processWages() {
	displayHeader();
	//createOutputFile(empArr, arrayLength);
	
	// create output file name
	char *outfile_basic = "Payroll_Week_Ending_";
	char *fileExtension = ".csv";
	
	//char *temp = strcat(*outfile_basic, getWEDate());
	char *WEDate = getWEDate();
	

	char *outfile = malloc(sizeof(outfile_basic) + sizeof(WEDate) + sizeof(fileExtension) + 1);
	
	strcpy(outfile, outfile_basic);
	outfile = strcat(outfile, WEDate);
	outfile = strcat(outfile, fileExtension);

	printText("Creating output file...");

	Sleep(2000);

	// create output file
	FILE* outptr = fopen(outfile, "w");
	if (outptr == NULL)
	{
		// TODO reimplement somehow
		//fclose(inptr);

		// create error message
		char *message = "Could not create ";
		char *messageFull = malloc(strlen(message) + 1 + strlen(outfile) + "...\n");
		strcpy(messageFull, message);
		strcat(messageFull, outfile);
		//strcat(messageFull, "...\n");

		printText(messageFull);

		Sleep(2000);

		// free memory
		free(messageFull);

	}
	else {
		printText("Output file created...");
	}

	// close outfile
	fclose(outptr);

	Sleep(2000);

	// free memory
	//free(outfile); // TODO Causing error

}

char * getWEDate() {
	
	// Declare Variables
	char *result;
	// get date
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	// get year
	char year[5];
	sprintf(year, "%d", tm.tm_year + 1900);

	// get month
	char month[3];
	char tempMonth[3];
	strcpy(month, "0");

	int monthNum = tm.tm_mon + 1;
	sprintf(tempMonth, "%d", monthNum);

	// add 0 if necessary
	if (monthNum / 10 == 0) {
		// convert int to char *
		strcat(month, tempMonth);
	}
	else
		strcpy(month, tempMonth);

	// get day
	char day[3];
	char tempDay[3];
	strcpy(day, "0");

	int dayNum = tm.tm_mday + 7 - tm.tm_wday; // gets date for Sunday of that week
	sprintf(tempDay, "%d", dayNum);

	// add 0 if necessary
	if (dayNum / 10 == 0)
		strcat(day, tempDay);
	else
		strcpy(day, tempDay);

	int temp = sizeof(year) + sizeof("-") + sizeof(day) + sizeof("-") + sizeof(month) + sizeof('\0');

	result = malloc(temp);
	// add year
	strcpy(result, year);
	result = strcat(result, "-");

	// add month
	result = strcat(result, month);
	result = strcat(result, "-");

	// add day
	result = strcat(result, day);

	result = strcat(result, "\0");
	return result;
}