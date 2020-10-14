/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "mem_alloc.h"



#include "ems_gc.h"

mem_allocator_t mem_allocator_create(void *mem, uint32_t size)
{
    return gc_init_with_pool((char *) mem, size);
}

void mem_allocator_destroy(mem_allocator_t allocator)
{
    gc_destroy_with_pool((gc_handle_t) allocator);
}

void *
mem_allocator_malloc(mem_allocator_t allocator, uint32_t size)
{
    return gc_alloc_vo((gc_handle_t) allocator, size);
}

void *
mem_allocator_realloc(mem_allocator_t allocator, void *ptr, uint32_t size)
{
    return gc_realloc_vo((gc_handle_t) allocator, ptr, size);
}

void mem_allocator_free(mem_allocator_t allocator, void *ptr)
{
    if (ptr)
        gc_free_vo((gc_handle_t) allocator, ptr);
}

int
mem_allocator_migrate(mem_allocator_t allocator,
                      mem_allocator_t allocator_old)
{
    return gc_migrate((gc_handle_t) allocator,
                      (gc_handle_t) allocator_old);
}

int
mem_allocator_reinit_lock(mem_allocator_t allocator)
{
    return gc_reinit_lock((gc_handle_t) allocator);
}

void
mem_allocator_destroy_lock(mem_allocator_t allocator)
{
    gc_destroy_lock((gc_handle_t) allocator);
}