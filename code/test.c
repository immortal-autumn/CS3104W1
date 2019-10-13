#include "myalloc.h"
#include <stdio.h>

#include <unistd.h>

// A simple test program to show the  use of the library
// By default, myalloc() simply calls malloc() so this will
// work.
// Kasim Terzic, Sep 2017

//test1 simple malloc test
void test1() {
    //first malloc
    printf("Allocating 1024 * sizeof(int)... \n");
    int* ptr1 = myalloc(1024*sizeof(int));
    //second malloc
    printf("Allocating 1024 * sizeof(int)... \n");
    int* ptr2 = myalloc(521 * sizeof(int));
    //third malloc
    printf("Allocating 1024 * sizeof(int)... \n");
    int* ptr3 = myalloc(1314 * sizeof(int));

    //first store
    ptr1[0] = -1;
    ptr1[1023] = -2;
    printf("Array 1: address %lu, value: %i\n", &ptr1[0], ptr1[0]);
    printf("Array 1: address %lu, value: %i\n", &ptr1[1023], ptr1[1023]);
    ptr2[0] = -1;
    ptr2[520] = -2;
    printf("Array 2: address %lu, value: %i\n", &ptr2[0], ptr2[0]);
    printf("Array 2: address %lu, value: %i\n", &ptr2[520], ptr2[520]);
    ptr3[0] = -1;
    ptr3[1313] = -2;
    printf("Array 3: address %lu, value: %i\n", &ptr3[0], ptr3[0]);
    printf("Array 3: address %lu, value: %i\n", &ptr3[1313], ptr3[1313]);


    //first free
    printf("Freeing the allocated memory... \n");
    myfree(ptr1);
    //second free
    printf("Freeing the allocated memory... \n");
    myfree(ptr2);
    //third free
    printf("Freeing the allocated memory... \n");
    myfree(ptr3);

    printf("Yay!\n");
}

//free space use test
void test2() {
    //first malloc
    printf("Allocating 1024 * sizeof(int)... \n");
    int* ptr1 = myalloc(1024*sizeof(int));

    //third malloc
    printf("Allocating 1024 * sizeof(int)... \n");
    int* ptr3 = myalloc(1314 * sizeof(int));

    //first store
    ptr1[0] = -1;
    ptr1[1023] = -2;
    printf("Array 1: address %lu, value: %i\n", &ptr1[0], ptr1[0]);
    printf("Array 1: address %lu, value: %i\n", &ptr1[1023], ptr1[1023]);

    //first free
    printf("Freeing the allocated memory... \n");
    myfree(ptr1);

    //second malloc
    printf("Allocating 1024 * sizeof(int)... \n");
    int* ptr2 = myalloc(521 * sizeof(int));

    ptr2[0] = -1;
    ptr2[520] = -2;
    printf("Array 2: address %lu, value: %i\n", &ptr2[0], ptr2[0]);
    printf("Array 2: address %lu, value: %i\n", &ptr2[520], ptr2[520]);

    ptr3[0] = -1;
    ptr3[1313] = -2;
    printf("Array 3: address %lu, value: %i\n", &ptr3[0], ptr3[0]);
    printf("Array 3: address %lu, value: %i\n", &ptr3[1313], ptr3[1313]);


    //second free
    printf("Freeing the allocated memory... \n");
    myfree(ptr2);
    //third free
    printf("Freeing the allocated memory... \n");
    myfree(ptr3);

    printf("Yay!\n");
}

int main(void)
{
    test2();
}
