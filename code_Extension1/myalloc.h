/*	Allocate 'size' bytes of memory. On success the function returns a pointer to 
	the start of the allocated region. On failure NULL is returned. 
	
	It will read through the free list, find a bigger space; if not, create a new node
	We need a global initial block for storing the head node
	However we need to override the malloc first.
*/
extern void *myalloc(int size);

/*	Release the region of memory pointed to by 'ptr'. */
extern void myfree(void *ptr);

/* Copy values in the memory to the destination */
extern void my_mem_cpy(void * target, void * dest, int size);

/* Change the size of the allocating memory */
extern void * myrealloc(void *ptr, int size);
