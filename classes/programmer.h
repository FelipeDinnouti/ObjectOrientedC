#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include "employee.h"

typedef struct Programmer Programmer;
typedef struct ProgrammerPrivate ProgrammerPrivate;
typedef struct ProgrammerVTable ProgrammerVTable;

// ---- Employee class
struct Programmer {
    // Inherited class
    Employee base;
    ProgrammerVTable* vtable;
    // Struct that stores private values
    ProgrammerPrivate* priv;
};

struct ProgrammerVTable {
    EmployeeVTable base;
    void (*do_code)(Programmer* programmer);
};

Programmer* ProgrammerCreate(const char* name, float salary, int department, unsigned long long int cpf, int birthdate);

#endif
