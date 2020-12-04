/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <string.h>

#include "bh_platform.h"
#include "bh_read_file.h"
#include "wasm_export.h"
#include "wasm_runtime_common.h"

#define USE_GLOBAL_HEAP_BUF 1
#define DEEPVM_HEAP_SIZE 16 * 1024
#define DEEPVM_STACK_SIZE 16 * 1024
#define DEEPVM_GLOBAL_HEAP_SIZE 10 * 1024 * 1024
#define MODULE_PATH ("--module-path=")

static int app_argc;
static char **app_argv;
static char global_heap_buf[DEEPVM_GLOBAL_HEAP_SIZE] = { 0 };

static void *
app_instance_main(wasm_module_inst_t module_inst)
{
    const char *exception;
    wasm_application_execute_main(module_inst, app_argc, app_argv);
    if ((exception = wasm_runtime_get_exception(module_inst)))
        printf("%s\n", exception);
    return NULL;
}

static int
native_puts (wasm_exec_env_t exec_env, const char *str)
{
    return printf("%s\n", str);
}

static int
native_putchar(wasm_exec_env_t exec_env, int c)
{
    printf("%c", c);
    return 1;
}

int
deep_wasm_vm_init (void)
{
    RuntimeInitArgs init_args;
    static NativeSymbol native_symbols[] = 
    {
        {"puts",native_puts, "($)i"},
        {"putchar",native_putchar, "(i)i"},

    };
    int n_native_symbols = sizeof(native_symbols) / sizeof(NativeSymbol);

    memset(&init_args, 0, sizeof(RuntimeInitArgs));

    init_args.mem_alloc_type = Alloc_With_Pool;
    init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
    init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);
    init_args.native_module_name = "env";
    init_args.native_symbols = native_symbols;
    init_args.n_native_symbols = n_native_symbols;
    
    /* initialize runtime environment */
    if (!wasm_runtime_full_init(&init_args)) {
        printf("Init runtime environment failed.\n");
        return -1;
    }
    return 0;
}

int
deep_wasm_eval (uint8 * wasm_buf, uint32 wasm_size)
{
    if (wasm_buf == NULL) {
        return -1;
    }
    char error_buf[128] = { 0 };
    uint32 stack_size = DEEPVM_HEAP_SIZE, heap_size = DEEPVM_STACK_SIZE;
    wasm_module_t wasm_module = NULL;
    wasm_module_inst_t wasm_module_inst = NULL;
    /* load WASM module */
    if (!(wasm_module = wasm_runtime_load(wasm_buf, wasm_size,
                                          error_buf, sizeof(error_buf)))) {
        printf("%s\n", error_buf);
        goto fail1;
    }
    /* instantiate the module */
    if (!(wasm_module_inst =
            wasm_runtime_instantiate(wasm_module, stack_size, heap_size,
                                     error_buf, sizeof(error_buf)))) {
        printf("%s\n", error_buf);
        goto fail3;
    }
    app_instance_main(wasm_module_inst);

    /* destroy the module instance */
    wasm_runtime_deinstantiate(wasm_module_inst);

fail3:
    /* unload the module */
    wasm_runtime_unload(wasm_module);

fail1:
    /* destroy runtime environment */
    wasm_runtime_destroy();
    return 0;
}

//int
//main (int argc, char *argv[])
//{
//    uint8 *wasm_file_buf = NULL;
//    uint32 wasm_file_size;
//    uint32 stack_size = DEEPVM_STACK_SIZE, heap_size = DEEPVM_HEAP_SIZE;
//    wasm_module_t wasm_module = NULL;
//    wasm_module_inst_t wasm_module_inst = NULL;
//    RuntimeInitArgs init_args;
//    char error_buf[128] = { 0 };
//#ifdef BUILD_TARGET_X86_64
//    debug ("BUILD_TARGET_X86_64");
//#endif
//
//#ifdef BUILD_TARGET_X86_32
//    debug ("BUILD_TARGET_X86_32");
//#endif
//    app_argc = argc;
//    app_argv = argv;
//    static NativeSymbol native_symbols[] =
//    {
//        {"puts",native_puts, "($)i"},
//        {"putchar",native_putchar, "(i)i"},
//    };
//    int n_native_symbols = sizeof(native_symbols) / sizeof(NativeSymbol);
//
//    memset(&init_args, 0, sizeof(RuntimeInitArgs));
//
//    init_args.mem_alloc_type = Alloc_With_Pool;
//    init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
//    init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);
//    init_args.native_module_name = "env";
//    init_args.native_symbols = native_symbols;
//    init_args.n_native_symbols = n_native_symbols;
//
//    /* initialize runtime environment */
//    if (!wasm_runtime_full_init(&init_args)) {
//        printf("Init runtime environment failed.\n");
//        return -1;
//    }
//
//    /* load WASM byte buffer from WASM bin file */
//    if (!(wasm_file_buf =
//            (uint8 *)bh_read_file_to_buffer(argv[1], &wasm_file_size)))
//        goto fail1;
//
//    /* load WASM module */
//    if (!(wasm_module = wasm_runtime_load(wasm_file_buf, wasm_file_size,
//                                          error_buf, sizeof(error_buf)))) {
//        printf("%s\n", error_buf);
//        goto fail2;
//    }
//    /* instantiate the module */
//    if (!(wasm_module_inst =
//            wasm_runtime_instantiate(wasm_module, stack_size, heap_size,
//                                     error_buf, sizeof(error_buf)))) {
//        printf("%s\n", error_buf);
//        goto fail3;
//    }
//    app_instance_main(wasm_module_inst);
//
//    /* destroy the module instance */
//    wasm_runtime_deinstantiate(wasm_module_inst);
//
//fail3:
//    /* unload the module */
//    wasm_runtime_unload(wasm_module);
//
//fail2:
//    /* free the file buffer */
//    wasm_runtime_free(wasm_file_buf);
//
//fail1:
//    /* destroy runtime environment */
//    wasm_runtime_destroy();
//    return 0;
//}
