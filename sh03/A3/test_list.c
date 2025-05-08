#include <stdio.h>
#include "mylist.h"


int main(int argc, char const *argv[])
{
    printf("hey there\n");

    list_t list;
    init_list(&list);
    print_list(&list);
    elem_t el1;
    el1.data = 3;
    append_elem(&list, &el1);
    print_list(&list);
    elem_t el2;
    el2.data = -1;
    append_elem(&list, &el2);
    print_list(&list);
    elem_t el3;
    el3.data = 5;
    append_elem(&list, &el3);
    print_list(&list);

    // elem_t rem_el;
    elem_t* rp;

    remove_elem(&list, &rp);
    print_list(&list);
    remove_elem(&list, &rp);
    print_list(&list);
    remove_elem(&list, &rp);
    print_list(&list);

     

    return 0;
}
