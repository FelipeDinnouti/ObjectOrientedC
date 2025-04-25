#ifndef PERSON_H
#define PERSON_H

// Forward declarations (opaque pointers)
typedef struct Person Person;
typedef struct PersonPrivate PersonPrivate;

// Virtual table used to override methods
typedef struct PersonVTable {
    void (*print)(Person*);
    void (*destroy)(Person*);
} PersonVTable;

// Global Struct
struct Person {
    PersonVTable* vtable; 
    // Surely can hold the 11 digits
    unsigned long long int cpf;
    // ddmmyyyyy - Eight digits.
    int birthdate;
};

// Constructor method
Person* PersonCreate(unsigned long long int cpf, int birthdate);

#endif