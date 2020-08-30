## wasm vm codereview

### 1.Main Entery

main函数中调用了的主要的函数。

```C
bool wasm_runtime_full_init(); /* 初始化wasm虚机 */
WASMModuleCommon *wasm_runtime_load(); /* 加载wasm文件 */
WASMModuleInstanceCommon *wasm_runtime_instantiate(); /* 实例化wasm module */
static void *app_instance_main(); /* main函数作为wasm module的入口，运行整个程序 */
```

### 2.C文件分析

#### 2.1文件列表

| 文件名                 | 功能介绍                                       |
| ---------------------- | ---------------------------------------------- |
| main.c                 | wasm虚机的主入口，初始化虚机，加载运行wasm文件 |
| wasm_c_api.c           |                                                |
| wasm_exec_env.c        |                                                |
| wasm_interp_classic.c  |                                                |
| wasm_loader.c          |                                                |
| wasm_memory.c          |                                                |
| wasm_native.c          |                                                |
| wasm_runtime.c         |                                                |
| wasm_runtime_common.c  |                                                |
| runtime_timer.c        |                                                |
| invokeNative_general.c |                                                |
| platform_init.c        |                                                |
| bh_assert.c            |                                                |
| bh_common.c            |                                                |
| bh_hashmap.c           |                                                |
| bh_list.c              |                                                |
| bh_log.c               | 日志系统，包括debug、dump等，已经自研了。      |
| bh_queue.c             |                                                |
| bh_read_file.c         |                                                |
| bh_vector.c            |                                                |
| ems_alloc.c            |                                                |
| ems_kfc.c              |                                                |
| libc_builtin_wrapper.c |                                                |
| mem_alloc.c            |                                                |
| posix_malloc.c         |                                                |
| posix_memmap.c         |                                                |
| posix_thread.c         |                                                |
| posix_time.c           |                                                |

#### 2.2main.c

##### 功能介绍

wasm虚机的主入口文件，包括初始化虚机、加载运行wasm文件等。

##### 对外接口

```C
int main() /* 整个虚机入口函数，前端要对接的就是该接口 */
```

#### 2.3wasm_c_api.c

##### 功能介绍

wasm虚机调用的C接口，包括XX、XX等。

##### 对外接口

```C
void wasm_byte_vec_new_uninitialized(); /* xxx */
void wasm_byte_vec_copy();/* xxx */
void wasm_byte_vec_new();/* xxx */
void wasm_byte_vec_delete();/* xxx */
wasm_engine_t *wasm_engine_new();/* xxx */
wasm_engine_t *wasm_engine_new_with_args();/* xxx */
void wasm_engine_delete(); /* xxx */
```

