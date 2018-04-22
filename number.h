#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED


#define BASIS 0xffff
typedef short Number_Coefficient;
typedef char  Bit;


typedef struct
{
    int   length;
    int   reserve;
    void *coefficients;
    int   basis;
}
Number;


void begin_number(Number *number, int basis);
    void add_element_in_number(Number *number, Number_Coefficient element);
void end_number(Number *number);

void add_number(Number *number1, Number *number2, Number *result);
void multiplicate_number(Number *number1, Number *number2, Number *result);

#include "number.c"

#endif //NUMBER_H_INCLUDED