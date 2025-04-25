#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "common.h"

static const int DAY_POS = 1000000;
static const int MONTH_POS = 10000;

void printlog(char* tag, char* message) {
    if (!DEBUG) return;

    long int t = clock();
    printf("[%ld] %s - %s", t, tag, message);
}
char* string_birthdate(int birthdate) {
    int day = birthdate/DAY_POS;
    int month = (birthdate-(DAY_POS*day))/MONTH_POS;
    int year = (birthdate-(DAY_POS*day)-(MONTH_POS*month));

    char* res = malloc(sizeof(char)*26);
    sprintf(res, "%d/%d/%d", day, month, year);

    return res;
}