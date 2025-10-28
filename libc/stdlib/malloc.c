#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

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
#define MAX_ORDER 8

extern int _end;

void *   heap_end;
void *   heap_start;
alloc_t *free_lists[MAX_ORDER + 1];

static bool grow_heap()
{
    if (!map_mem(heap_end)) return false;
    heap_end += 4096;
    return true;
}

void _init_malloc()
{
    heap_end = &_end;
    heap_end = (void *)(((uintptr_t)heap_end + 4095) & ~4095);
    heap_start = heap_end;
    if (!grow_heap()) exit(1);
    heap_start = heap_end - 4096;
    alloc_t *root = (alloc_t *)heap_start;
    root->order = MAX_ORDER;
    root->used = false;
    root->next = NULL;
    root->prev = NULL;
    for (int i = 0; i <= MAX_ORDER; i++) free_lists[i] = NULL;
    free_lists[MAX_ORDER] = root;
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
    }
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
    if (!grow_heap()) return NULL;
    alloc_t *new_block = (alloc_t *)((char *)heap_end - 4096);
    new_block->order = MAX_ORDER;
    new_block->used = false;
    new_block->next = free_lists[MAX_ORDER];
    new_block->prev = NULL;
    if (free_lists[MAX_ORDER]) free_lists[MAX_ORDER]->prev = new_block;
    free_lists[MAX_ORDER] = new_block;
    // recursive call
    return malloc(size);
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

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
