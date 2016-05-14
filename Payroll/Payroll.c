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
				case '7':
					break;

				default:
					printText("\n  Invalid selection...");
					printText("\n  Please select an option from the menu [1-7]: ");

			}

		} while (input < '1' || input > '7');

		/*switch (input) {
		case '1':
			displayEmployees(employees, arrayLength);

			break;

		case '2':
			//newEmployee();
			break;

		case '3':
			//setCurrentEmployee(char *name, bool b);
			break;

		case '4':
			//changeDept(char *name, Department_t dept)
			break;

		case '5':
			//changeRate(char *name, Rate_t rate)
			break;

		case '6':
			processWages(employees, arrayLength);
			break;

		case '7':
			break;

		default:
			if (input == '\n')
				continue;

			printf("\nUnrecognised Command - Please enter value from 1-7:");
		}*/

	} while (input != '7');

	//processWages();

	printText("\nExiting program...\n");

	// that's all folks
	return 0;
}





/* Processes wages for employees and save to file */
void processWages(Employee_t empArr[]) { //TODO reimplement
//void processWages() {

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

	// create output file name
	char *outfile_basic = "Payroll_Week_Ending_";
	int temp = sizeof(outfile_basic) + sizeof(year) + sizeof("-") + sizeof(3) + sizeof("-") + sizeof(3) + sizeof(".csv") + '\0';
	char *outfile = malloc(temp);

	outfile = strcpy(outfile, outfile_basic);

	// add year
	outfile = strcat(outfile, year);
	outfile = strcat(outfile, "-");

	// add month
	outfile = strcat(outfile, month);
	outfile = strcat(outfile, "-");

	// add day
	outfile = strcat(outfile, day);
	outfile = strcat(outfile, ".csv");

	printText("Creating output file...\n");

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
		strcat(messageFull, "...\n");

		printText(messageFull);

		Sleep(2000);

		// free memory
		free(messageFull);

		printText("Exiting program...\n");
		//fprintf(stderr, "Could not create %s.\n", outfile);
		return 3;
	}
	else {
		printText("Output file created...\n");
	}

	// close outfile
	fclose(outptr);

	// free memory
	//free(outfile); // TODO Causing error

}
