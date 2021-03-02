#include <stdlib.h>

/*
 * This is a rather simple malloc implementation (written by foliagecanine)
 * It is not particularly efficient with small allocations, but handles large ones fairly well.
 *
 * When an allocation is made, it attempts to make a new allocation in the remaining unused space.
 * If there is not enough space, it will simply allocate more memory than needed.
 *
 * In some cases, a zero-length allocation will be made in the remaining space.
 * The effect is no different than if no allocation were made EXCEPT if the allocation after the
 * zero-length one is freed, it can reclaim the space used by the freed allocation's alloc_t structure.
 *
 * The free function will attempt to reclaim the allocation after the freed allocation, as well as
 * before the freed allocation:
 * [Used][Unused][To be freed][Unused][Used] -> [Used][Unused][Used]
 * This should prevent any memory from being lost.
 * 
 * The realloc function will try to merge the allocation with the current alloc or the alloc after the current alloc (if it's free).
 * If both of these fail, it will call malloc with the new size and copy the existing data.
 * 
 * The calloc function just calls the malloc function and memsets it.
 *
 * TODO:
 * If the last allocation passes through a 4096 byte boundary and is freed, give the memory back to the kernel.
 *
 */

typedef struct alloc_t alloc_t;

struct alloc_t {
	size_t size;
	bool used;
	alloc_t *next;
	alloc_t *prev;
};

extern int _end;

void *heap_end;
alloc_t *root_alloc;
alloc_t *last_alloc;

static bool grow_heap() {
	if (!map_mem(heap_end))
		return false;
	heap_end += 4096;
	return true;
}

void _init_malloc() {
	heap_end = &_end;
	heap_end -= ((uintptr_t)(&_end) % 4096);
	heap_end += 4096;
	root_alloc = heap_end;
	last_alloc = root_alloc;
	if (!grow_heap())
		exit(1); // Kill process if not enough memory to begin heap.
	root_alloc->size = 4096;
	root_alloc->used = false;
	root_alloc->next = NULL;
	root_alloc->prev = NULL;
}

int printf(const char *format, ...);

void *malloc(size_t size) {
	alloc_t *current_alloc = root_alloc;
	while(true) {
		while (current_alloc->used) {
			current_alloc = current_alloc->next;
		}
		if (current_alloc->size == size) {
			// If it is the last alloc, we will need to create one after this.
			// Grow the heap and treat it as current_alloc->size > size.
			if (current_alloc == last_alloc) {
				if (!grow_heap())
					return 0;
				current_alloc->size += 4096;
			} else {
				current_alloc->used = true;
				return (void *)(current_alloc) + sizeof(alloc_t);
			}
		}
		if (current_alloc->size > size) {
			if (current_alloc->size < size + sizeof(alloc_t) + sizeof(alloc_t)) {
				// Not enough space for a new alloc. Treat as if equal.
				if (current_alloc == last_alloc) {
					if (!grow_heap())
						return 0;
					current_alloc->size += 4096;
					// Assume sizeof(alloc_t) < 4096
				} else {
					current_alloc->used = true;
					return (void *)(current_alloc) + sizeof(alloc_t);
				}
			}
			alloc_t *new_alloc = (void *)(current_alloc) + sizeof(alloc_t) + size;
			
			new_alloc->used = false;
			new_alloc->size = current_alloc->size - (sizeof(alloc_t) + size);
			new_alloc->next = current_alloc->next;
			new_alloc->prev = current_alloc;

			if (new_alloc->next == NULL)
				last_alloc = new_alloc;
			
			current_alloc->used = true;
			current_alloc->size = size;
			current_alloc->next = new_alloc;
			// prev is same
			
			return (void *)(current_alloc) + sizeof(alloc_t);
		}
		if (current_alloc == last_alloc && current_alloc->size < size) {
			while (true) {
				if (!grow_heap())
					return 0;
				current_alloc->size += 4096;
				if (current_alloc->size >= size)
					break;
			}
		} else if (current_alloc->size < size) {
			current_alloc = current_alloc->next;
		}
	}
}

void free(void *ptr) {
	alloc_t *current_alloc = ptr - sizeof(alloc_t);
	current_alloc->used = false;
	
	alloc_t *next_alloc = current_alloc->next;
	alloc_t *prev_alloc = current_alloc->prev;

	if (next_alloc && !next_alloc->used) {
		current_alloc->next = next_alloc->next;
		current_alloc->size += next_alloc->size + sizeof(alloc_t);
		if (current_alloc->next == NULL)
				last_alloc = current_alloc;
	}
	
	
	if (prev_alloc && !prev_alloc->used) {
		prev_alloc->next = current_alloc->next;
		prev_alloc->size += current_alloc->size + sizeof(alloc_t);
		if (prev_alloc->next == NULL)
				last_alloc = prev_alloc;
	}
}

void *realloc(void *ptr, size_t size) {
	alloc_t *current_alloc = ptr - sizeof(alloc_t);
	if (current_alloc->size >= size) {
		if ((current_alloc->size - size) >= sizeof(alloc_t)) {
			alloc_t *new_alloc = current_alloc + sizeof(alloc_t) + size + sizeof(alloc_t);
			new_alloc->used = false;
			new_alloc->size = (current_alloc->size - size) - sizeof(alloc_t);
			new_alloc->next = current_alloc->next;
			new_alloc->prev = current_alloc;
			
			// Still used
			current_alloc->size = size;
			current_alloc->next = new_alloc;
			// prev is same
			
			return ptr;
		}
		// Not enough space to make new alloc_t structure, return the same memory
		return ptr;
	}
	if (!current_alloc->next->used && current_alloc->next->size + current_alloc->size >= size) {
		alloc_t *reclaim_alloc = current_alloc->next;
		current_alloc->next = reclaim_alloc->next;
		current_alloc->size += reclaim_alloc->size + sizeof(alloc_t);
		// Treat it as greater or equal
		if ((current_alloc->size - size) >= sizeof(alloc_t)) {
			alloc_t *new_alloc = current_alloc + sizeof(alloc_t) + size + sizeof(alloc_t);
			new_alloc->used = false;
			new_alloc->size = (current_alloc->size - size) - sizeof(alloc_t);
			new_alloc->next = current_alloc->next;
			new_alloc->prev = current_alloc;
			
			// Still used
			current_alloc->size = size;
			current_alloc->next = new_alloc;
			// prev is same
			
			return ptr;
		}
		// Not enough space to make new alloc_t structure, return the same memory
		return ptr;
	}
	
	// We cannot fit it in any existing allocations.
	void *alloced_mem = malloc(size);
	memcpy(alloced_mem, ptr, current_alloc->size);
	return alloced_mem;
}

void *calloc(size_t num, size_t size) {
	void *retval = malloc(num*size);
	memset(retval, 0, num*size);
	return retval;
}