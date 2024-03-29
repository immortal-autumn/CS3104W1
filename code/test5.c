/*	Stuart Norcross - 12/03/10 */

/* This program allocates integer arrays and displays trace information*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "myalloc.h"

#define INTS_PER_ALLOCATION 10

int alloc_size=sizeof(int)*INTS_PER_ALLOCATION;

void check_failed(int val){
	fprintf(stderr, "Check failed for region with value %i.",val);
	exit(-1);
}

void check(int *mem, int value){
	int i;
	for(i=0;i<INTS_PER_ALLOCATION;i++){
		if(mem[i]!=value)check_failed(value);
	}
}

void set(int *mem, int value){
	int i;
	for(i=0;i<INTS_PER_ALLOCATION;i++){
		mem[i]=value;
	}
}

int *alloc_and_set(int value){
	int* mem = (int*)myalloc(alloc_size);
	set(mem,value);
	return mem;
}

int main(int argc, char* argv[]){
	printf("%s starting\n",argv[0]);

	// allocate
	void *p0 = alloc_and_set(1);printf("TEST 5-0 PASSED - ALLOCATED\n");
	check(p0,1);
	void *p1 = alloc_and_set(2);printf("TEST 5-1 PASSED - ALLOCATED\n");
	check(p1,2);
	void *p2 = alloc_and_set(3);printf("TEST 5-2 PASSED - ALLOCATED\n");
	check(p2,3);
	void *p3 = alloc_and_set(4);printf("TEST 5-3 PASSED - ALLOCATED\n");
	check(p3,4);
	void *p4 = alloc_and_set(5);printf("TEST 5-4 PASSED - ALLOCATED\n");
	check(p4,5);
	void *p5 = alloc_and_set(6);printf("TEST 5-5 PASSED - ALLOCATED\n");
	check(p5,6);
	
	//free
	myfree(p0);
	printf("TEST 5-6 PASSED - FREED\n");
	myfree(p2);
	printf("TEST 5-7 PASSED - FREED\n");
	myfree(p4);
	printf("TEST 5-8 PASSED - FREED\n");

	printf("%s complete\n",argv[0]);
	
}
