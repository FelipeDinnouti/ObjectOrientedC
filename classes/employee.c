#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "employee.h"

// Declaration of struct that handles private members
typedef struct EmployeePrivate {
    char *name;    
    float salary;
    int department;
    bool is_working;
} EmployeePrivate;

static void employee_print_impl(Person* person) {
    // Safe cast because person is the first member
    Employee* self = (Employee*)person;

    printf("Funcionario: %s\n - Salario: %.2fR$\n - Departamento: %s\n", self->priv->name, self->priv->salary, DepartmentMap[self->priv->department]);
    return; 
}

static void employee_destroy_impl(Person* person) {
    printlog("EmployeeDestroy", "Destroying\n");

    Employee* self = (Employee*) person;

    // Free its own resources
    free(self->priv->name);
    free(self->priv);

    // Free its parent resources
    // Self is Employee, base is Person, I call destroy on Person passing base(Person) as the parameter.
    PersonVTable* person_vtable = (PersonVTable *) self->base.vtable;
    person_vtable->destroy((Person*) &self->base);

    printlog("EmployeeDestroy", "Finalizing\n");
}

static void employee_clock_in(Employee* employee) {
    // Negates the bool, is either working or not, and changes that when the employee clocks it.
    employee->priv->is_working = !employee->priv->is_working;
    printf("Funcionario \"%s\" Bateu Ponto!\n", employee->priv->name);
}

// Getters and setters
static char* get_name(Employee* employee) {
    return employee->priv->name;
}
static float get_salary(Employee* employee) {
    return employee->priv->salary;
}
static int get_department(Employee* employee) { 
    return employee->priv->department;
}
static bool is_working(Employee* employee) {
    return employee->priv->is_working;
}

static void set_name(Employee* employee, char* new_name) {
    employee->priv->name = new_name;
}
static void set_salary(Employee* employee, float new_salary) {
    employee->priv->salary = new_salary;
}
static void set_department(Employee* employee, int new_department) {
    employee->priv->department = new_department;
}
static void set_is_working(Employee* employee, bool new_state) {
    employee->priv->is_working = new_state;
}

// One VTable for all objects.
static EmployeeVTable employee_vtable = {
    // Overriding inherited methods
    .base = {
        .print = employee_print_impl,
        .destroy = employee_destroy_impl
        },
    // Employee methods
    .clock_in = employee_clock_in,
    .get_name = get_name,
    .get_salary = get_salary,
    .get_department = get_department,
    .is_working = is_working,

    .set_name = set_name,
    .set_salary = set_salary,
    .set_department = set_department,
    .set_is_working = set_is_working,

};

// Constructor Method -
Employee* EmployeeCreate(const char* name, float salary, int department, unsigned long long int cpf, int birthdate) {
    printlog("EmployeeCreate", "Allocating employee\n");
    Employee* self = malloc(sizeof(Employee));
    EmployeePrivate* emp_priv = malloc(sizeof(EmployeePrivate));

    // Creating inherited object
    self->base = *PersonCreate(cpf, birthdate);
    
    // Creating private object
    self->priv = emp_priv;

    // Setting values
    printlog("EmployeeCreate", "Allocating name\n");
    self->priv->name = strdup(name);
    self->priv->department = department;
    self->priv->salary = salary;

    printlog("EmployeeCreate", "Setting pointers\n");
    self->vtable = &employee_vtable;

    printlog("EmployeeCreate", "Employee Allocated!\n");
    return self;
}