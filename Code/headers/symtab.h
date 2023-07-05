#ifndef PJAVA_SYMTAB_H
#define PJAVA_SYMTAB_H

#include "boolean.h"

typedef struct _symtab{
    char *string;
    int intValue;
    double doubleValue;
    float floatValue;
    bool boolValue;
} symtab;

#endif
