/**
* CompanyPayroll
*
* FIT ICTAP Procedural Programming Assignment
*
* Author Philip Woulfe
* Version 1.0
* 2016-10-05
* Body for creation of UI
*/

#define _CRT_SECURE_NO_DEPRECATE

// used to underline text for UI 
#define ANSI_UNDERLINED_PRE  "\033[4m"
#define ANSI_UNDERLINED_POST "\033[0m"

#include "PayrollUI.h"

/* Displays the header for the program */
void displayHeader(void) {
	printf("  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("  *          _      _   _____   _     ___                                         *\n");
	printf("  *         | |    | | |  _  | | |   |  _|                                        *\n");
	printf("  *         | | /\\ | | | | | | | |   | |_                                         *\n");
	printf("  *         | |//\\\\| | | |_| | | |_  |  _|                                        *\n");
	printf("  *         |__/  \\__| |_____| |___| |_|                                          *\n");
	printf("  *                                                                               *\n");
	printf("  *                 ____     ___   __   __  ____    _____   _     _   TM          *\n");
	printf("  *                |  _ \\   / _ \\  \\ \\ / / |  _ \\  |  _  | | |   | |              *\n");
	printf("  *                | |_| | | |_| |  \\ v /  | |_| | | | | | | |   | |              *\n");
	printf("  *                |  __/  |  _  |   | |   |  _ <  | |_| | | |_  | |_             *\n");
	printf("  *                |_|     |_| |_|   |_|   |_| |_| |_____| |___| |___|            *\n");
	printf("  *                                                                               *\n");
	printf("  *                                   © Copyright Wolf Accounting 2016            *\n");
	printf("  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

}

/* Clears the command screen */
void clearScreen(void) {
	system("cls");
}

/* Prints text to console 1 character at a time */
void printText(char *text) {

	// Formatting
	printf("  ");

	for (int i = 0; text[i] != '\0'; i++) {
		printf("%c", text[i]);
		fflush(stdout); // outputs to console 1 char at a time instead of buffering all first
		Sleep(10);
	}

	Sleep(50);
}

/* Display main menu */
void displayMenu(void) {

	clearScreen();
	displayHeader();

	printText("Welcome to the Wolf Accounting Payroll System.\n\n");
	printText("1. View Employees\n");
	printText("2. Add Employee\n");
	printText("3. Change Employee Employment status\n");
	printText("4. Change Employee Department\n");
	printText("5. Change Employee Pay Rate\n");
	printText("6. Calculate Payroll for this week\n");
	printText("7. Quit\n\n");
	printText("Please select an option from the menu [1-7]: ");

}

/* Display Employees */
void displayEmployees(Employee_t employees[], int arrayLength) {

	clearScreen();
	displayHeader();
	//printf("  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("   _______________________________________________________________________________\n");
	printf("  |                                                                               |\n");
	printf("  |                    Wolf Payroll - Display Current Employees                   |\n");
	printf("  | " ANSI_UNDERLINED_PRE "                                                                             " ANSI_UNDERLINED_POST " |\n");
	printf("  | " ANSI_UNDERLINED_PRE " # | Name                                   | Department          | Pay Rate " ANSI_UNDERLINED_POST " |\n");
	printf("  |    |                                        |                     |           |\n");

	for (int i = 0; i < arrayLength; i++) {

		// Skip former employees
		if (!employees[i].currentEmployee) {
			continue;
		}

		//printf(employees[i--].name);
		char* name = malloc(sizeof(employees[i].name[0]));
		strcpy(name, employees[i].name);
		//printf(name);
		//getchar();
		char* dept = "";
		char* rate = "";

		// Set Department
		switch (employees[i].dept) {
		case 1:
			dept = "HR";
			break;
		case 2:
			dept = "IT";
			break;
		case 3:
			dept = "Production";
			break;
		case 4:
			dept = "Sales & Marketing";
			break;
		default:
			printText("How the hell did you manage that?");
		}

		// Set pay rate
		switch (employees[i].rate) {
		case 1:
			rate = "Associate";
			break;
		case 2:
			rate = "Senior";
			break;
		case 3:
			rate = "Manager";
			break;
		default:
			printText("Seriously, how are you doing this?");
		}

		bool current = employees[i].currentEmployee;

		//printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		//printf("  | Number | Name                   | Department          | Pay Rate  |\n");
		printf("  | %2d | %-38s | %-19s | %-9s |\n", i + 1, name, dept, rate, current ? "true" : "false");

	}

	printf("  |____|________________________________________|_____________________|___________|\n");
	printText("Press any key to continue...");
	getch();
}
