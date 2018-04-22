void copy_memory(void *destination, void *source, unsigned int length)
{
    unsigned int r;

    r = length % sizeof(char*);
    length = (length - r) / sizeof(char*);

    for(; length; --length)
    {
        *((char**)destination) = *((char**)source);

        destination += sizeof(char*);
        source += sizeof(char*);
    }

    for(; r; --r)
    {
        *((char*)destination) = *((char*)source);

        destination += 1;
        source += 1;
    }
}


void swap(void *data1, void *data2, unsigned int length)
{
    char         *big_tmp;
    char          small_tmp;
    unsigned int  r;

    r = length % sizeof(char*);
    length = (length - r) / sizeof(char*);

    for(; length; --length)
    {
        big_tmp = *((char**)data1);
        *((char**)data1) = *((char**)data2);
        *((char**)data2) = big_tmp;

        data1 += sizeof(char*);
        data2 += sizeof(char*);
    }

    for(; r; --r)
    {
        small_tmp = *((char*)data1);
        *((char*)data1) = *((char*)data2);
        *((char*)data2) = small_tmp;

        data1 += 1;
        data2 += 1;
    }
}


unsigned int size_of_basis(Number *number)
{
    return (number->basis - 1) / 256 + 1;
}


void begin_number(Number *number, int basis)
{
    number->reserve = 1;
    number->length = 0;
    number->basis = basis;
    number->coefficients = malloc(size_of_basis(number));
}


void add_element_in_number(Number *number, Number_Coefficient element)
{
    void *new_data;

    if(number->length == number->reserve)
    {
        number->reserve *= 2;
        new_data = malloc(number->reserve * size_of_basis(number));
        copy_memory(new_data, number->coefficients, number->length * size_of_basis(number));
        free(number->coefficients);
        number->coefficients = new_data;
    }

    copy_memory(number->coefficients + number->length * size_of_basis(number), &element, size_of_basis(number));
    ++number->length;
}


void end_number(Number *number)
{
    free(number->coefficients);
}


void print_number(Number *number)
{
    int                i;
    Number_Coefficient c;

    for(i = 0; i < number->length; ++i)
    {
        c = 0;
        copy_memory(&c, number->coefficients + i * size_of_basis(number), size_of_basis(number));

        printf("%d ", c);
    }
}


void add_number(Number *number1, Number *number2, Number *result)
{
    int i;
    Number_Coefficient c1;
    Number_Coefficient c2;
    Number_Coefficient c;
    Number_Coefficient r;

    r = 0;
    c1 = 0;
    c2 = 0;

    if(number1->length > number2->length)
        swap(&number1, &number2, sizeof(Number**));

    for(i = 0; i < number1->length; ++i)
    {
        copy_memory(&c1, number1->coefficients + i * size_of_basis(number1), size_of_basis(number1));
        copy_memory(&c2, number2->coefficients + i * size_of_basis(number2), size_of_basis(number2));

        c = c1 + c2 + r;
        r = c / result->basis;
        c = c % result->basis;

        add_element_in_number(result, c);
    }

    for(; i < number2->length; ++i)
    {
        copy_memory(&c2, number2->coefficients + i * size_of_basis(number2), size_of_basis(number2));

        c = c2 + r;
        r = c / result->basis;
        c = c % result->basis;

        add_element_in_number(result, c);
    }

    if(r)
        add_element_in_number(result, r);
}


void multiplicate_number(Number *number1, Number *number2, Number *result)
{
    
}