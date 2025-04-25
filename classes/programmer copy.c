#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "programmer.h"

// Declaration of struct that handles private members
typedef struct ProgrammerPrivate {
    char *name;    
    float salary;
    int department;
    bool is_working;
} ProgrammerPrivate;

static void programmer_print_impl(Person* person) {
    // Safe cast because person is the first member
    Programmer* self = (Programmer*) person;
    Employee* base = &self->base;
    
    printf("Programador: %s\n - Salario: %.2fR$\n - Departamento: %s\n", 
        base->vtable->get_name(base), 
        base->vtable->get_salary(base), 
        DepartmentMap[base->vtable->get_department(base)]);
    return; 
}

static void programmer_destroy_impl(Person* person) {
    printlog("ProgrammerDestroy", "Destroying\n");

    Programmer* self = (Programmer*) person;

    // Free its own members
    free(self->priv);

    // Free inherited class (recursively) by calling the destroy() on the parent class
    EmployeeVTable* employee_vtable = (EmployeeVTable*) self->base.vtable;
    employee_vtable->base.destroy((Person*) &self->base);
    
    printlog("ProgrammerDestroy", "Finalizing Destroy\n");
}

// This is a function inherited from Employee*, therefore the signature must match
static void programmer_clock_in(Employee* employee) {
    Programmer* programmer = (Programmer*) employee;
    Employee* base = &programmer->base;

    // Negates the bool, is either working or not, and changes that when the employee clocks it.
    base->vtable->set_is_working(base, !base->vtable->is_working(base));

    printf("Programador \"%s\" bateu ponto!\n", programmer->base.vtable->get_name((Employee*) programmer));
}

static void programmer_do_code(Programmer* programmer) {
    EmployeeVTable* employee_vtable = (EmployeeVTable*) programmer->base.vtable;
    printf("Programador \"%s\" esta a programar...\n", employee_vtable->get_name((Employee*) programmer)); // Segfault
}

// One VTable for all objects.
static ProgrammerVTable programmer_vtable = {
    // Overriding inherited methods
    
    // Employee
    .base = {
        // Person
        .base = {
            .print = programmer_print_impl,
            .destroy = programmer_destroy_impl
        },
        .clock_in = programmer_clock_in,
        },

    // Programmer methods
    .do_code = programmer_do_code,
};

// Constructor Method -
Programmer* ProgrammerCreate(const char* name, float salary, int department, unsigned long long int cpf, int birthdate) {
    printlog("ProgrammerCreate", "Allocating employee\n");
    Programmer* self = malloc(sizeof(Programmer));
    ProgrammerPrivate* prog_priv = malloc(sizeof(ProgrammerPrivate));

    printlog("ProgrammerCreate", "Setting pointers\n");
    // Creating inherited object, setting base by value and not by pointer
    self->base = *EmployeeCreate(name, salary, department, cpf, birthdate);
    self->vtable = &programmer_vtable;

    // Creating private object
    self->priv = prog_priv;


    printlog("ProgrammerCreate", "Programmer Allocated!\n");
    return self;
}