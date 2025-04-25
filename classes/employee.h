#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdbool.h>

// Inherited class
#include "person.h"


typedef struct Employee Employee;
typedef struct EmployeePrivate EmployeePrivate;
typedef struct EmployeeVTable EmployeeVTable;

// ---- Employee class
struct Employee {
    // Inherited class
    Person base;
    EmployeeVTable* vtable;
    // Struct that stores private values
    EmployeePrivate* priv;
};

struct EmployeeVTable {
    // Inherited class's VTable
    PersonVTable base;
    // Methods
    void (*clock_in)(Employee*);

    // Getter and setter
    void (*set_name)(Employee*, char* new_name);
    void (*set_salary)(Employee*, float new_salary);
    void (*set_department)(Employee*, int new_department);
    void (*set_is_working)(Employee*, bool new_state);

    char* (*get_name)(Employee*);
    float (*get_salary)(Employee*);
    int (*get_department)(Employee*);
    bool (*is_working)(Employee*);
};

Employee* EmployeeCreate(const char* name, float salary, int department, unsigned long long int cpf, int birthdate);

#endif
