#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

// Debugging
static const bool DEBUG = true;

// Constants
static const char* DepartmentMap[] = {"Human Resources","Logistics", "Administration"}; 

// Enumerator class
typedef enum {
    HR,
    LOGISTICS,
    ADMIN
} Department;

// Functions
void printlog(char* tag, char* message);
char* string_birthdate(int birthdate);

#endif