#ifndef _DEEP_MEM_ALLOC_H
#define _DEEP_MEM_ALLOC_H

#include "bh_platform.h"

bool deep_mem_init (void *mem, uint32_t size);

void deep_mem_destroy (void);

void *deep_malloc (uint32_t size);

void *deep_realloc (void *ptr, uint32_t size);

void deep_free (void *ptr);

bool deep_mem_migrate (void *new_mem, uint32_t size);

#endif /* _DEEP_MEM_ALLOC_H */
