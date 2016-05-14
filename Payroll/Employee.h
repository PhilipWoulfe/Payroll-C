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

} Employee_t;