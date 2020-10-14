/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "wasm_exec_env.h"
#include "wasm_runtime_common.h"

#if WASM_ENABLE_THREAD_MGR != 0
#include "thread_manager.h"
#endif

WASMExecEnv *
wasm_exec_env_create_internal(struct WASMModuleInstanceCommon *module_inst,
                              uint32 stack_size)
{
    uint64 total_size = offsetof(WASMExecEnv, wasm_stack.s.bottom)
                        + (uint64)stack_size;
    WASMExecEnv *exec_env;

    if (total_size >= UINT32_MAX
        || !(exec_env = wasm_runtime_malloc((uint32)total_size)))
        return NULL;

    memset(exec_env, 0, (uint32)total_size);




    exec_env->module_inst = module_inst;
    exec_env->wasm_stack_size = stack_size;
    exec_env->wasm_stack.s.top_boundary =
        exec_env->wasm_stack.s.bottom + stack_size;
    exec_env->wasm_stack.s.top = exec_env->wasm_stack.s.bottom;
    return exec_env;

    wasm_runtime_free(exec_env);
    return NULL;
}

void
wasm_exec_env_destroy_internal(WASMExecEnv *exec_env)
{
#ifdef OS_ENABLE_HW_BOUND_CHECK
    WASMJmpBuf *jmpbuf = exec_env->jmpbuf_stack_top;
    WASMJmpBuf *jmpbuf_prev;
    while (jmpbuf) {
        jmpbuf_prev = jmpbuf->prev;
        wasm_runtime_free(jmpbuf);
        jmpbuf = jmpbuf_prev;
    }
#endif
    wasm_runtime_free(exec_env);
}

WASMExecEnv *
wasm_exec_env_create(struct WASMModuleInstanceCommon *module_inst,
                     uint32 stack_size)
{
    WASMExecEnv *exec_env = wasm_exec_env_create_internal(module_inst,
                                                          stack_size);
    /* Set the aux_stack_boundary to 0 */
    exec_env->aux_stack_boundary = 0;
    return exec_env;
}

void
wasm_exec_env_destroy(WASMExecEnv *exec_env)
{
#if WASM_ENABLE_THREAD_MGR != 0
    /* Terminate all sub-threads */
    WASMCluster *cluster = wasm_exec_env_get_cluster(exec_env);
    if (cluster) {
        wasm_cluster_terminate_all_except_self(cluster, exec_env);
        wasm_cluster_del_exec_env(cluster, exec_env);
    }
#endif
    wasm_exec_env_destroy_internal(exec_env);
}

WASMModuleInstanceCommon *
wasm_exec_env_get_module_inst(WASMExecEnv *exec_env)
{
    return exec_env->module_inst;
}

void
wasm_exec_env_set_thread_info(WASMExecEnv *exec_env)
{
    exec_env->handle = os_self_thread();
    exec_env->native_stack_boundary = os_thread_get_stack_boundary()
                                      + RESERVED_BYTES_TO_NATIVE_STACK_BOUNDARY;
}


#ifdef OS_ENABLE_HW_BOUND_CHECK
void
wasm_exec_env_push_jmpbuf(WASMExecEnv *exec_env, WASMJmpBuf *jmpbuf)
{
    jmpbuf->prev = exec_env->jmpbuf_stack_top;
    exec_env->jmpbuf_stack_top = jmpbuf;
}

WASMJmpBuf *
wasm_exec_env_pop_jmpbuf(WASMExecEnv *exec_env)
{
    WASMJmpBuf *stack_top = exec_env->jmpbuf_stack_top;

    if (stack_top) {
        exec_env->jmpbuf_stack_top = stack_top->prev;
        return stack_top;
    }

    return NULL;
}
#endif

