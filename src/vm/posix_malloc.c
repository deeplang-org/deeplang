/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "deep_mem_alloc.h"
#include "platform_api_vmcore.h"

void *
os_malloc(unsigned size)
{
    return deep_malloc(size);
}

void *
os_realloc(void *ptr, unsigned size)
{
    return deep_realloc(ptr, size);
}

void
os_free(void *ptr)
{
    deep_free(ptr);
}



