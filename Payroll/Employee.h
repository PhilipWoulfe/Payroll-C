/**
* CompanyPayroll
*
* FIT ICTAP Procedural Programming Assignment
*
* Author Philip Woulfe
* Version 1.0
* 2016-10-05
* Header for creation of Employee Data type
*/

#ifndef __Employee_h__
#define __Employee_h__

#include <stdbool.h>

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
	float weeksWages;

} Employee_t;



/* Create a new employee*/
void newEmployee(char *name, Department_t dept, Rate_t rate);

/* Changes employee's department */
void changeDept(char *name, Department_t dept);

/* Change employee's pay rate */
void changeRate(char *name, Rate_t rate);

/* Terminate or rehire employees */
void setCurrentEmployee(char *name, bool b);


#endif /* __Employee_h_ */