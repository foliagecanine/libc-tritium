#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys.h>


/*
 * Blockwise malloc implementation using a buddy allocator.
 * This allocates memory in blocks of powers of two sizes.
 */

typedef struct alloc_t alloc_t;

struct alloc_t
{
    int      order;
    bool     used;
    alloc_t *next;
    alloc_t *prev;
    char     data[];
};

#define MIN_BLOCK_SIZE 16
#define MAX_ORDER 27
#define PAGE_ORDER 8

extern int _end;

void *   heap_end;
void *   heap_start;
alloc_t *free_lists[MAX_ORDER + 1];

static bool grow_heap(int order)
{
    if (order < PAGE_ORDER) order = PAGE_ORDER;
    size_t block_size = (size_t)MIN_BLOCK_SIZE << order;

    // Fill alignment gap with page-sized blocks to avoid unmapped holes
    while ((uintptr_t)heap_end & (block_size - 1)) {
        if (!map_mem(heap_end)) return false;
        alloc_t *gap_block = (alloc_t *)heap_end;
        gap_block->order = PAGE_ORDER;
        gap_block->used = true;
        heap_end = (void *)((uintptr_t)heap_end + 4096);
        free(gap_block->data);
    }

    // Now heap_end is aligned to block_size. Map the requested block.
    for (uintptr_t i = 0; i < block_size; i += 4096) {
        if (!map_mem((void *)((uintptr_t)heap_end + i))) return false;
    }

    alloc_t *new_block = (alloc_t *)heap_end;
    heap_end = (void *)((uintptr_t)heap_end + block_size);
    
    new_block->order = order;
    new_block->used = true;
    free(new_block->data);

    return true;
}

void _init_malloc()
{
    heap_end = &_end;
    heap_end = (void *)(((uintptr_t)heap_end + 4095) & ~4095);
    heap_start = heap_end;
    for (int i = 0; i <= MAX_ORDER; i++) free_lists[i] = NULL;
    if (!grow_heap(PAGE_ORDER)) exit(1);
}

void *malloc(size_t size)
{
    if (size == 0) return NULL;
    size_t required = size + sizeof(alloc_t);
    int order = 0;
    size_t block_size = MIN_BLOCK_SIZE;
    while (block_size < required) {
        order++;
        block_size <<= 1;
        if (order > MAX_ORDER) return NULL;
        if (block_size == 0) return NULL; // Overflow check
    }
    
    while(1) {
        for (int o = order; o <= MAX_ORDER; o++) {
            if (free_lists[o]) {
                alloc_t *block = free_lists[o];
                // remove from free list
                free_lists[o] = block->next;
                if (free_lists[o]) free_lists[o]->prev = NULL;
                block->used = true;
                // split down to order
                for (int i = o; i > order; i--) {
                    alloc_t *buddy = (alloc_t *)((char *)block + (MIN_BLOCK_SIZE << (i - 1)));
                    buddy->order = i - 1;
                    buddy->used = false;
                    buddy->next = free_lists[i - 1];
                    buddy->prev = NULL;
                    if (free_lists[i - 1]) free_lists[i - 1]->prev = buddy;
                    free_lists[i - 1] = buddy;
                    block->order = i - 1;
                }
                return block->data;
            }
        }
        // grow heap
        if (!grow_heap(order)) return NULL;
    }
}

void free(void *ptr)
{
    if (!ptr) return;
    alloc_t *block = (alloc_t *)((char *)ptr - sizeof(alloc_t));
    if (block->used == false) return; // already free?
    block->used = false;
    int order = block->order;
    // merge with buddy
    while (order < MAX_ORDER) {
        alloc_t *buddy = (alloc_t *)((uintptr_t)block ^ (MIN_BLOCK_SIZE << order));
        if ((char *)buddy < (char *)heap_start || (char *)buddy >= (char *)heap_end || buddy->used || buddy->order != order) break;
        // remove buddy from free list
        alloc_t **list = &free_lists[order];
        while (*list) {
            if (*list == buddy) {
                *list = buddy->next;
                if (*list) (*list)->prev = buddy->prev;
                if (buddy->prev) buddy->prev->next = *list;
                break;
            }
            list = &(*list)->next;
        }
        // merge
        if (buddy < block) block = buddy;
        block->order = order + 1;
        order++;
    }
    // add to free list
    block->next = free_lists[order];
    block->prev = NULL;
    if (free_lists[order]) free_lists[order]->prev = block;
    free_lists[order] = block;
}

void *realloc(void *ptr, size_t size)
{
    if (!ptr) return malloc(size);
    alloc_t *block = (alloc_t *)((char *)ptr - sizeof(alloc_t));
    size_t current_size = (MIN_BLOCK_SIZE << block->order) - sizeof(alloc_t);
    if (current_size >= size) return ptr;
    void *new_ptr = malloc(size);
    if (!new_ptr) return NULL;
    memcpy(new_ptr, ptr, current_size);
    free(ptr);
    return new_ptr;
}

void *calloc(size_t num, size_t size)
{
    void *ptr = malloc(num * size);
    if (!ptr) return NULL;
    memset(ptr, 0, num * size);
    return ptr;
}
