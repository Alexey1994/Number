#include "number.h"


void test_print()
{
    Number n;

    begin_number(&n, 10);
        add_element_in_number(&n, 1);
        add_element_in_number(&n, 2);

        print_number(&n);
    end_number(&n);
}


void test_add()
{
    Number n1;
    Number n2;
    Number n1_plus_n2;

    begin_number(&n1, 10);
        add_element_in_number(&n1, 2);
        add_element_in_number(&n1, 1);
        add_element_in_number(&n1, 3);

        begin_number(&n2, 10);
            add_element_in_number(&n2, 9);

            begin_number(&n1_plus_n2, 10);
                add_number(&n1, &n2, &n1_plus_n2);

                print_number(&n1_plus_n2);
            end_number(&n1_plus_n2);
        end_number(&n2);
    end_number(&n1);
}


int main()
{
    test_add();

    return 0;
}