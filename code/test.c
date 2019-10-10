#include "myalloc.h"
#include <stdio.h>

#include <unistd.h>

// A simple test program to show the  use of the library
// By default, myalloc() simply calls malloc() so this will
// work.
// Kasim Terzic, Sep 2017

int main(void)
{
    printf("Allocating 1024 * sizeof(int)... \n");

    int* ptr = myalloc(1024*sizeof(int));
    ptr[1023] = 123;
    // printf("%lu\n%lu\n", &ptr[0], ptr);

    printf("Freeing the allocated memory... \n");
    myfree(ptr);

    printf("Yay!\n");
}
