/*Stuart Norcross - 12/03/10 */

/* Ver - 7.10.2019.1 - Malloc without thread safe */

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

/* Create the initial memory zone when no memory allocated. */
t_head * create_init() {
	int size = 17 << 10; // 5 pages to malloc (.1.)
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

/*
malloc: read through the free list, find a bigger space; if not, create a new node
We need a global initial block for storing the head node
However we need to override the malloc first.
*/
void * myalloc(int size){
	if (size <= 0) return MALLOC_FAILED;
	if (init == NULL) {
		if (MAP_FAILED == (init = create_init())) return MALLOC_FAILED;
		init -> size = size;
		init -> next = NULL;
		init -> free = IS_USE;
		// printf("FREE BLOCK: %i, %lu\n", init -> free, &(init -> free));
		return (void*)init + block_size;
	}
	else {
		t_head * ptr = init;
		while (ptr -> free == IS_USE || ptr -> size < size) {
			if (ptr -> next == NULL) {
				ptr -> next = create_next(size, ptr + block_size);
				return ptr + block_size;
			}
		}
		return ptr + block_size;
	}
}

void myfree(void *ptr){
	t_head * node = ptr - block_size;
	// printf("FREE BLOCK: %i, %lu\n", node -> free, &(node -> free));
	if (node -> free == IS_USE) {
		node -> free = IS_FREE;
	}
	else {
		printf("Free failed!\n");
	}
}
