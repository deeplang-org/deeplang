/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "wasm_runtime_common.h"
#include "bh_platform.h"
#include "mem_alloc.h"


#ifndef MALLOC_MEMORY_FROM_SYSTEM

// seems that Intel WASM allows memory to be used in 2 modes.
typedef enum Memory_Mode {
    MEMORY_MODE_UNKNOWN = 0,
    MEMORY_MODE_POOL,
    MEMORY_MODE_ALLOCATOR
} Memory_Mode;

static Memory_Mode memory_mode = MEMORY_MODE_UNKNOWN;

// for pool mode
static mem_allocator_t pool_allocator = NULL;

// for allocator mode
static void *(*malloc_func)(unsigned int size) = NULL;
static void *(*realloc_func)(void *ptr, unsigned int size) = NULL;
static void (*free_func)(void *ptr) = NULL;

// for pool mode
static unsigned int global_pool_size;

static bool
wasm_memory_init_with_pool(void *mem, unsigned int bytes)
{
    // TODO? using a default allocator?
    mem_allocator_t _allocator = mem_allocator_create(mem, bytes);

    if (_allocator) {
        memory_mode = MEMORY_MODE_POOL;
        pool_allocator = _allocator;
        global_pool_size = bytes;
        return true;
    }
    LOG_ERROR("Init memory with pool (%p, %u) failed.\n", mem, bytes);
    return false;
}

static bool
wasm_memory_init_with_allocator(void *_malloc_func,
                                void *_realloc_func,
                                void *_free_func)
{
    if (_malloc_func && _free_func && _malloc_func != _free_func) {
        memory_mode = MEMORY_MODE_ALLOCATOR;
        malloc_func = _malloc_func;
        realloc_func = _realloc_func;
        free_func = _free_func;

        return true;
    }
    LOG_ERROR("Init memory with allocator (%p, %p, %p) failed.\n",
              _malloc_func, _realloc_func, _free_func);
    return false;
}

// alloc_option is a `union`, combining options for two modes
bool
wasm_runtime_memory_init(mem_alloc_type_t mem_alloc_type,
                         const MemAllocOption *alloc_option)
{
    if (mem_alloc_type == Alloc_With_Pool)
        return wasm_memory_init_with_pool(alloc_option->pool.heap_buf,
                                          alloc_option->pool.heap_size);
    else if (mem_alloc_type == Alloc_With_Allocator)
        return wasm_memory_init_with_allocator(alloc_option->allocator.malloc_func,
                                               alloc_option->allocator.realloc_func,
                                               alloc_option->allocator.free_func);
    else if (mem_alloc_type == Alloc_With_System_Allocator)
        // this option does not use any other functions in this file.
        return wasm_memory_init_with_allocator(os_malloc, os_realloc, os_free);
    else
        return false;
}

void
wasm_runtime_memory_destroy()
{
#if BH_ENABLE_MEMORY_PROFILING != 0
    os_mutex_destroy(&profile_lock);
#endif
    if (memory_mode == MEMORY_MODE_POOL)
        mem_allocator_destroy(pool_allocator);
    memory_mode = MEMORY_MODE_UNKNOWN;
}

// default size: 1 GB (unit: Byte) when not in pool mode
unsigned
wasm_runtime_memory_pool_size()
{
    if (memory_mode == MEMORY_MODE_POOL)
        return global_pool_size;
    else
        return 1 * BH_GB;
}

void *
wasm_runtime_malloc(unsigned int size)
{
    if (memory_mode == MEMORY_MODE_UNKNOWN) {
        LOG_WARNING("wasm_runtime_malloc failed: memory hasn't been initialized.\n");
        return NULL;
    } else if (memory_mode == MEMORY_MODE_POOL) {
        // TODO? associated malloc func in mem_alloc.c?
        return mem_allocator_malloc(pool_allocator, size);
    } else {
        // provided during initialisation
        return malloc_func(size);
    }
}

void *
wasm_runtime_realloc(void *ptr, unsigned int size)
{
    if (memory_mode == MEMORY_MODE_UNKNOWN) {
        LOG_WARNING("wasm_runtime_realloc failed: memory hasn't been initialized.\n");
        return NULL;
    } else if (memory_mode == MEMORY_MODE_POOL) {
        return mem_allocator_realloc(pool_allocator, ptr, size);
    } else {
        // TODO? Does this mean `realloc_func` is optional?
        if (realloc_func)
            return realloc_func(ptr, size);
        else
            return NULL;
    }
}

void
wasm_runtime_free(void *ptr)
{
    if (memory_mode == MEMORY_MODE_UNKNOWN) {
        LOG_WARNING("wasm_runtime_free failed: memory hasn't been initialized.\n");
    } else if (memory_mode == MEMORY_MODE_POOL) {
        mem_allocator_free(pool_allocator, ptr);
    } else {
        free_func(ptr);
    }
}

#if BH_ENABLE_MEMORY_PROFILING != 0


#endif /* end of BH_ENABLE_MEMORY_PROFILING */

#else /* else of MALLOC_MEMORY_FROM_SYSTEM */

#endif /* end of MALLOC_MEMORY_FROM_SYSTEM*/
