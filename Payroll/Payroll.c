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

// used to underline text for UI 
#define ANSI_UNDERLINED_PRE  "\033[4m"
#define ANSI_UNDERLINED_POST "\033[0m"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/* Declare enums */
typedef enum {
	HR = 1,
	IT = 2,
	PRODUCTION = 3,
	SALES_AND_MARKETING = 4
} Department_t;

typedef enum {
	ASSOCIATE = 1,
	SENIOR = 2,
	MANAGER = 3,
} Rate_t;

/* create employe data type */
typedef struct {
	char name[50];
	Department_t dept;
	Rate_t rate;
	bool currentEmployee;

} Employee_t;

/* Display Header */
void displayHeader(void);

/* Clear command screen */
void clearScreen(void);

/* Load text with character delay */
void printText(char *text);

/* Display main menu */
void displayMenu(void);

/* Load Employees */
int loadEmployees(Employee_t employees[], int arrayLength);

/* Get fields from csv */
const char* getfield(char* line, int num);

/* Display Employees */
void displayEmployees(Employee_t employees[], int arrayLength);

/* Create a new employee*/
void newEmployee(char *name, Department_t dept, Rate_t rate);

/* Changes employee's department */
void changeDept(char *name, Department_t dept);

/* Change employee's pay rate */
void changeRate(char *name, Rate_t rate);

/* Terminate or rehire employees */
void setCurrentEmployee(char *name, bool b);

/* Save current employees to file */
void saveEmployeesToFile(Employee_t empArr[], int arrayLength);

/* Processes wages for employees */
void processWages(Employee_t empArr[], int arrayLength);
//void processWages(); //TODO Reimplement

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

	clearScreen();
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
