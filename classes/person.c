#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "person.h"


// Root class Person
static void person_print_impl(Person* self) {
    printf("Person:\n - CPF: %llu\n", self->cpf);
}
static void person_destroy_impl(Person* self) {
    printlog("Person Destroy", "Destroying\n");
    // Since person is the top class, it frees self (the whole struct).
    free(self);
    return;
}

static PersonVTable person_vtable = {
    .print = person_print_impl,
    .destroy = person_destroy_impl
};

Person* PersonCreate(unsigned long long int cpf, int birthdate) {
    printlog("PersonCreate", "Allocating Person\n");
    Person* self = malloc(sizeof(Person));

    self->vtable = &person_vtable;
    self->cpf = cpf;
    self->birthdate = birthdate;

    printlog("PersonCreate", "Person Allocated!\n");
    return self;
}