/*Stuart Norcross - 12/03/10 */

/* Ver - 12.10.2019.2 - Malloc with */

#define _GNU_SOURCE //Define MAP_ANONYMOUS
#define MALLOC_FAILED MAP_FAILED
#define IS_FREE 0
#define IS_USE 1

#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "myalloc.h"

typedef struct Header {
	size_t size;
	struct Header * next;
	char free; 
} t_head;

/*
next is a void pointer type which is used to store the address of next block.
block size is the sum of size of t_head and size_t and one char.
Block is used to save meta data
*/
static const size_t block_size = sizeof(t_head); 
static t_head * init = NULL;

/* Create the critical initial memory zone when no memory allocated. */
t_head * create_init() {
	int size = 25 << 20; // 26214400 bytes, coverts to 25 MB in binary
	t_head * new_zone = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	return new_zone;
}

/* Create the next meta block. */
t_head * create_next(int size, void * addr) {
	t_head * block = addr;
	block -> next = NULL;
	block -> size = size;
	block -> free = IS_USE; 
	return block;
}

void * list_read(int size, t_head * node) {
	if (node -> free == IS_FREE && node -> size >= size) {
		node -> free = IS_USE;
		return (void*)node + block_size;
	}
	if (node -> next == NULL) {
		node -> next = create_next(size, (void*)node + block_size + node -> size);
		return (void*)(node -> next) + block_size;
	}
	return list_read(size, node -> next);
}

void * myalloc(int size){
	printf("Processing: size %i\n", size);
	if (size <= 0) return MALLOC_FAILED;
	if (init == NULL) {
		if (MAP_FAILED == (init = create_init())) return MALLOC_FAILED;
		init -> size = size;
		init -> next = NULL;
		init -> free = IS_USE;
		return (void*)init + block_size;
	}
	else {
		return list_read(size, init);
	}
}

void myfree(void *ptr){
	t_head * node = ptr - block_size;
	// printf("Node of %lu status: %i\n", ptr, node -> free);
	if (node -> free == IS_USE) {
		node -> free = IS_FREE;
		char* arrow = ptr;
		for (int i = 0; i < node -> size; i++) { //initialise the space
			*arrow = 0;
			arrow++;
		}
	}
	else {
		printf("Free failed!\n");
	}
	// printf("Node of %lu freed status: %i\n", ptr, node -> free);
}

void my_mem_cpy(void * target, void * dest, int size) {
	char* tar = target;
	char* dest_val = dest;
	for (int i = 0; i < size; i++) {
		dest_val[i] = tar[i];
	}
}

/*
realloc: 4 situations
if memory not allocated : Allocate memory with size
if size = 0 : Free and return nothing
if size >= ptr -> size: Malloc a larger space, mem_copy it
if size < ptr -> size: Malloc a smaller space, delete the data after ptr
*/
void * myrealloc(void *ptr, int size) {
	t_head * node = ptr - block_size;
	if (node -> free == IS_FREE) {
		return myalloc(size);
	}
	else{
		if (size == 0) {
			myfree(ptr);
			return MALLOC_FAILED;
		}
		if (size >= node -> size) {
			void * new_ptr = myalloc(size);
			my_mem_cpy(ptr, new_ptr, node -> size);
			myfree(ptr);
			return new_ptr;
		}
		if (size < node -> size) {
			int sub = node -> size - size;
			char* dest = ptr;
			for(int i = 0; i < sub; i++) {
				dest[size + i] = 0;
			}
			return (void*)dest;
		}
	}
	return MALLOC_FAILED;	
}