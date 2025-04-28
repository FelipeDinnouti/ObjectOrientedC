#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "classes/person.h"
#include "classes/employee.h"
#include "classes/programmer.h"
#include "classes/common.h"

#define MAX_NAME_LIMIT 40

// To illustrate functionalities with default values
void example() {
    Person* person = PersonCreate(12332112344ULL, 24022009);

    printf("Person Pointer: %p\n", &person);

    person->vtable->print(person);
    person->vtable->destroy(person);

    Employee* employee = EmployeeCreate("Carlos", 500.0f, LOGISTICS, 987654321ULL, 12022009);
    printf("Employee Pointer> %p\n", &employee);

    employee->vtable->clock_in(employee);

    // Casting to Person* since it is the root class, and therefore the functions require Person* parameters
    // A cast does not change how the data is stored, just how it is treated by the compiler
    employee->vtable->base.print((Person*) employee);
    
    Programmer* programmer = ProgrammerCreate("Joao", 1000.0f, ADMIN, 51487440812ULL, 2022009);

    // Vtables are static, shared between every object.
    printf("programmer->vtable->base.base.destroy (Programmer Vtable): %p\n", programmer->vtable);
    printf("programmer->base.vtable->base.destroy (Employee Vtable): %p\n", programmer->base.vtable);
    printf("programmer->base.base.vtable->destroy (Person Vtable): %p\n\n", programmer->base.base.vtable);

    printf("employee->vtable->base.destroy (Employee Vtable): %p\n", employee->vtable);
    printf("employee->base.vtable->destroy (Person Vtable): %p\n", employee->base.vtable);

    // Normal call
    programmer->vtable->base.clock_in((Employee*) programmer);
    // Super call
    programmer->base.vtable->clock_in((Employee*) programmer);

    // Programmer method, no cast needed
    programmer->vtable->do_code(programmer);
    
    // Employee method, no cast needed
    employee->vtable->clock_in(employee);

    // Base person methods on both
    programmer->vtable->base.base.print((Person*) programmer);
    employee->vtable->base.print((Person*) employee);

    programmer->vtable->base.base.destroy((Person*) programmer);
    employee->vtable->base.destroy((Person*) employee);
}

// Read input from user
unsigned long long int GetCPF() {
    bool correct = false;
    unsigned long long int cpf;

    //          99999999999 max cpf
    const unsigned long long int MAX = 100000000000;

    while (!correct) {
        printf("Insira o CPF: ");
        scanf("%llu", &cpf);
        printf("\n");

        if (cpf<MAX) 
        {   
            correct = true;
        } else {
            printf("CPF Invalido\n");
        }
    }
    
    return cpf;
}

int GetBirthdate() {
    bool correct = false;
    int birthdate = 0;

    while (!correct) {
        printf("Insira a data de nascimento (ddmmaaaa, sem separação): ");
        scanf("%d", &birthdate);
        // Max is   100000000
        //          00112222
        if (birthdate<100000000) {
            correct = true;
        } else {
            printf("Data invalida");
        }
    }

}

char* GetName() {
    char* str[MAX_NAME_LIMIT];
    printf("Insira o nome:");
    fgets(str, MAX_NAME_LIMIT, stdin);
    
    return str;
}

float GetSalary() {
    float salary;
    printf("Input salary: ");
    scanf("%f", &salary);
    return salary;
}

int GetDepartment() {
    int department;
    printf("Choose a department:\n1 - Human Resources\n2 - Logistics\n3 - Administration\n\nOption: ");
    scanf("%d", &department);
    return department;
}

const char* MAIN_MENU = "Bem vindo ao sistema de gerenciamento de funcionários!";

// Example constructor
Person* InteractivePersonCreate() {
    // Input CPF (11 digits):
    unsigned long long int cpf = GetCPF();
    int birthdate = GetBirthdate();
    Person* res = PersonCreate(cpf, birthdate);

    return res;
}

Employee* InteractiveEmployeeCreate() {
    // Person
    unsigned long long int cpf = GetCPF();
    int birthdate = GetBirthdate();
    
    // Employee
    char* name = GetName;
    float salary = GetSalary();
    int department = GetDepartment();

    Employee* employee = EmployeeCreate(name, salary, department, cpf, birthdate);
    
    return employee;
}

Programmer* InteractiveProgrammerCreate() {
    // Person
    unsigned long long int cpf = GetCPF();
    int birthdate = GetBirthdate();
    
    // Employee
    char* name = GetName;
    float salary = GetSalary();
    int department = GetDepartment();

    Programmer* programmer = EmployeeCreate(name, salary, department, cpf, birthdate);
    
    return programmer;
}

Person* persons[32] = {};
int persons_length = 0;

int main() {
    // example();

    // Main menu
    
    
    InteractivePersonCreate();

    printf("%s", string_birthdate(12121999));

    return 0;
}