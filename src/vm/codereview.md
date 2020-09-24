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

| 文件名                 | 功能介绍                                                     |
| ---------------------- | ------------------------------------------------------------ |
| main.c                 | wasm虚机的主入口，初始化虚机，加载运行wasm文件。             |
| wasm_c_api.c           | wasm虚机调用的C接口，包括对一些基本数据类型的创建、初始化、回收等。 |
| wasm_exec_env.c        |                                                              |
| wasm_interp_classic.c  |                                                              |
| wasm_loader.c          | 包含负责将wasm模块载入内存的接口。                           |
| wasm_memory.c          | wasm 虚机调用的内存初始化、分配、释放相关的接口。 |
| wasm_native.c          |                                                              |
| wasm_runtime.c         | 模块运行时所需接口，如：实例化模块、验证模块、载入环境等。   |
| wasm_runtime_common.c  |                                                              |
| runtime_timer.c        |                                                              |
| invokeNative_general.c |                                                              |
| platform_init.c        | 初始化平台环境，目前为空。                                   |
| bh_assert.c            | assert接口。                                                 |
| bh_common.c            |                                                              |
| bh_hashmap.c           |                                                              |
| bh_list.c              |                                                              |
| bh_log.c               | 日志系统，包括debug、dump等，已经自研了。                    |
| bh_queue.c             |                                                              |
| bh_read_file.c         |                                                              |
| bh_vector.c            | 提供vector的实现与操作接口。                                 |
| ems_alloc.c            |                                                              |
| ems_kfc.c              |                                                              |
| libc_builtin_wrapper.c |                                                              |
| mem_alloc.c            |                                                              |
| posix_malloc.c         |                                                              |
| posix_memmap.c         |                                                              |
| posix_thread.c         | 线程管理接口。                                               |
| posix_time.c           | 时间戳获取接口。                                             |

#### 2.2main.c

##### 功能介绍

wasm虚机的主入口文件，包括初始化虚机、加载运行wasm文件等。

##### 对外接口

```C
int main() /* 整个虚机入口函数，前端要对接的就是该接口 */
```

#### 2.3wasm_c_api.c

##### 功能介绍

wasm虚机调用的C接口，包括对一系列基本数据类型的创建、初始化、回收等。

##### 对外接口

```C
void wasm_byte_vec_new_uninitialized(wasm_byte_vec_t *out, size_t size);
/* 初始化wasm_byte_vec_t *out大小为size，清空为0 */
void wasm_byte_vec_copy(wasm_byte_vec_t *out, const wasm_byte_vec_t *src);
/* 将src内容复制到out */
void wasm_byte_vec_new(wasm_byte_vec_t *out, size_t size, const wasm_byte_t *data);
/* 使用长度为size的数组data初始化out */
void wasm_byte_vec_delete(wasm_byte_vec_t *byte_vec);
/* 回收wasm_byte_vec_t的内存 */

wasm_engine_t *wasm_engine_new();
/* 创建wasm_engine_t，单例模式，已有则直接返回 */
wasm_engine_t *wasm_engine_new_with_args(mem_alloc_type_t type,
                          const MemAllocOption *opts,
                          runtime_mode_e mode);
/* 使用空间分配模式、运行模式等参数新建singleton wasm_engine_t */
void wasm_engine_delete(wasm_engine_t *engine);
/* 删除回收wasm_engint_t */

wasm_store_t *wasm_store_new(wasm_engine_t *engine);
/* 创建wasm_store_t，已有则返回第一个 */
void wasm_store_delete(wasm_store_t *store);
/* 删除回收wasm_store_t */
void wasm_store_vec_new_uninitialized(wasm_store_vec_t *out, size_t size);
/* 创建未初始化的指定大小的wasm_store_vec_t */
void wasm_store_vec_delete(wasm_store_vec_t *store_vec);
/* 删除回收wasm_store_vec_t */

wasm_valtype_t *wasm_valtype_new(wasm_valkind_t kind);
/* 根据wasm_valkind_t创建wasm_valtype_t */
void wasm_valtype_delete(wasm_valtype_t *val_type);
/* 删除回收wasm_valtype_t */
wasm_valtype_t *wasm_valtype_copy(wasm_valtype_t *src);
/* 复制wasm_valtype_t *src，返回新的wasm_valtype_t* */
wasm_valkind_t wasm_valtype_kind(const wasm_valtype_t *val_type);
/* 获取wasm_valtype_t*的wasm_valkind_t */
bool wasm_valtype_same(const wasm_valtype_t *vt1, const wasm_valtype_t *vt2);
/* 判断两个wasm_valtype_t是否相同 */

void wasm_valtype_vec_new_uninitialized(wasm_valtype_vec_t *out, size_t size);
/* 创建未初始化的指定大小的wasm_valtype_vec_t */
void wasm_valtype_vec_new_empty(wasm_valtype_vec_t *out);
/* 创建一个空的wasm_valtype_vec_t */
void wasm_valtype_vec_new(wasm_valtype_vec_t *out,
                     size_t size,
                     wasm_valtype_t *const data[]);
/* 通过数组创建新的wasm_valtype_vec_t */
void wasm_valtype_vec_copy(wasm_valtype_vec_t *out, const wasm_valtype_vec_t *src);
/* 复制wasm_valtype_vec_t */
void wasm_valtype_vec_delete(wasm_valtype_vec_t *val_type_vec);
/* 删除回收wasm_valtype_vec_t */

wasm_functype_t *wasm_functype_new(wasm_valtype_vec_t *params, wasm_valtype_vec_t *results);
/* 创建新的wasm_functype_t */
wasm_functype_t *wasm_functype_copy(wasm_functype_t *src);
/* 复制wasm_functype_t */
void wasm_functype_delete(wasm_functype_t *func_type);
/* 删除wasm_functype_t */
const wasm_valtype_vec_t *wasm_functype_params(const wasm_functype_t *func_type);
/* 获取函数类型的参数类型 */
const wasm_valtype_vec_t *wasm_functype_results(const wasm_functype_t *func_type);
/* 获取函数类型的返回类型 */

wasm_globaltype_t *wasm_globaltype_new(wasm_valtype_t *val_type, wasm_mutability_t mut);
/* 创建新的wasm_globaltype_t */
void wasm_globaltype_delete(wasm_globaltype_t *global_type);
/* 删除wasm_globaltype_t */
wasm_globaltype_t *wasm_globaltype_copy(wasm_globaltype_t *src);
/* 复制wasm_globaltype_t */
const wasm_valtype_t *wasm_globaltype_content(const wasm_globaltype_t *global_type);
/* 获取wasm_globaltype_t对应的wasm_valtype_t */
wasm_mutability_t wasm_globaltype_mutability(const wasm_globaltype_t *global_type);
/* 获取wasm_globaltype_t对应的wasm_mutability_t */
bool wasm_globaltype_same(const wasm_globaltype_t *gt1, const wasm_globaltype_t *gt2);
/* 判断两个wasm_globaltype_t是否相同 */

wasm_tabletype_t *wasm_tabletype_new(wasm_valtype_t *val_type, const wasm_limits_t *limits);
/* 创建新的wasm_tabletype_t */
void wasm_tabletype_delete(wasm_tabletype_t *table_type);
/* 删除wasm_tabletype_t */

wasm_memorytype_t *wasm_memorytype_new(const wasm_limits_t *limits);
/* do nothing */
void wasm_memorytype_delete(wasm_memorytype_t *memory_type);
/* do nothing */

void wasm_val_delete(wasm_val_t *v);
/* do nothing */
void wasm_val_copy(wasm_val_t *out, const wasm_val_t *src);
/* 复制wasm_val_t */
bool wasm_val_same(const wasm_val_t *v1, const wasm_val_t *v2);
/* 判断两个wasm_val_t是否相同 */

wasm_trap_t *wasm_trap_new(wasm_store_t *store, const wasm_message_t *message);
/* 新建wasm_trap_t */
void wasm_trap_delete(wasm_trap_t *trap);
/* 删除wasm_trap_t */
void wasm_trap_message(const wasm_trap_t *trap, wasm_message_t *out);
/* 获取wasm_trap_t中信息 */

wasm_module_t *wasm_module_new(wasm_store_t *store, const wasm_byte_vec_t *binary);
/* 新建wasm_trap_t */
void wasm_module_delete_internal(wasm_module_t *module);
/* 删除wasm_module_t */
void wasm_module_delete(wasm_module_t *module);
/* do nothing */

void wasm_module_vec_new_uninitialized(wasm_module_vec_t *out, size_t size);
/* 不初始化地新建wasm_module_vec_t */
void wasm_module_vec_delete(wasm_module_vec_t *module_vec);
/* 删除wasm_module_vec_t */

wasm_func_t *wasm_func_new(wasm_store_t *store,
              const wasm_functype_t *func_type,
              wasm_func_callback_t callback);
/* 新建wasm_func_t */
wasm_func_t * wasm_func_new_with_env(wasm_store_t *store,
                       const wasm_functype_t *func_type,
                       wasm_func_callback_with_env_t callback,
                       void *env,
                       void (*finalizer)(void *));
/* 通过env创建wasm_func_t */
void wasm_func_delete(wasm_func_t *func);
/* 删除wasm_func_t */
wasm_func_t *wasm_func_copy(const wasm_func_t *func);
/* 复制wasm_func_t */
wasm_functype_t *wasm_func_type(const wasm_func_t *func);
/* 获取wasm_func_t对应的wasm_functype_t */
wasm_trap_t *wasm_func_call(const wasm_func_t *func,
               const wasm_val_t params[],
               wasm_val_t results[]);
/* 调用wasm_func_t对应函数 */
size_t wasm_func_param_arity(const wasm_func_t *func);
/* 获取wasm_func_t参数占用空间大小 */
size_t wasm_func_result_arity(const wasm_func_t *func);
/* 获取wasm_func_t结果占用空间大小 */
wasm_extern_t *wasm_func_as_extern(wasm_func_t *func);
/* 将wasm_func_t转换为wasm_extern_t */


wasm_global_t *wasm_global_new(wasm_store_t *store,
                const wasm_globaltype_t *global_type,
                const wasm_val_t *init);
/* 新建wasm_global_t */
wasm_global_t *wasm_global_copy(const wasm_global_t *src);
/* 复制wasm_global_t */
void wasm_global_delete(wasm_global_t *global);
/* 删除wasm_global_t */
bool wasm_global_same(const wasm_global_t *g1, const wasm_global_t *g2);
/* 判断两个wasm_global_t是否相同 */
void wasm_global_set(wasm_global_t *global, const wasm_val_t *v);
/* 为wasm_global_t赋值 */
void wasm_global_get(const wasm_global_t *global, wasm_val_t *out);
/* 获取wasm_global_t的值 */
wasm_globaltype_t *wasm_global_type(const wasm_global_t *global);
/* 获取wasm_global_t对应的wasm_globaltype_t */
wasm_extern_t *wasm_global_as_extern(wasm_global_t *global);
/* 将wasm_global_t转换为wasm_extern_t */

void wasm_table_delete(wasm_table_t *table);
 /* do nothing */
void wasm_memory_delete(wasm_memory_t *memory);
 /* do nothing */

wasm_extern_t *wasm_extern_copy(const wasm_extern_t *src);
/* 复制wasm_extern_t */
void wasm_extern_delete(wasm_extern_t *external);
/* 回收wasm_extern_t */
wasm_externkind_t wasm_extern_kind(const wasm_extern_t *extrenal);
/* 获取对应的wasm_externkind_t */
wasm_func_t *wasm_extern_as_func(wasm_extern_t *external);
/* 将wasm_extern_t转换为wasm_func_t */
const wasm_func_t *wasm_extern_as_func_const(const wasm_extern_t *external);
/* 将wasm_extern_t转换为wasm_func_t */
wasm_global_t *wasm_extern_as_global(wasm_extern_t *external);
/* 将wasm_extern_t转换为wasm_global_t */
const wasm_global_t *wasm_extern_as_global_const(const wasm_extern_t *external);
/* 将wasm_extern_t转换为wasm_global_t */
wasm_memory_t *wasm_extern_as_memory(wasm_extern_t *external);
/* 将wasm_extern_t转换为wasm_memory_t */
const wasm_memory_t *wasm_extern_as_memory_const(const wasm_extern_t *external);
/* 将wasm_extern_t转换为wasm_memory_t */
wasm_table_t *wasm_extern_as_table(wasm_extern_t *external);
/* 将wasm_extern_t转换为wasm_table_t */
const wasm_table_t *wasm_extern_as_table_const(const wasm_extern_t *external);
/* 将wasm_extern_t转换为wasm_table_t */
void wasm_extern_vec_copy(wasm_extern_vec_t *out, const wasm_extern_vec_t *src);
/* 复制wasm_extern_vec_t */
void wasm_extern_vec_new_uninitialized(wasm_extern_vec_t *out, size_t size);
/* 新建wasm_extern_vec_t */
void wasm_extern_vec_delete(wasm_extern_vec_t *extern_vec);
/* 删除wasm_extern_vec_t */
```

#### 2.4 wasm_loader.c

##### 功能介绍

虚机解释器模块。

##### 对外接口

```c
WASMModule* wasm_loader_load(const uint8 *buf, uint32 size, char *error_buf, uint32 error_buf_size);
/* 从字节码buf中载入大小为size的模块 */

void wasm_loader_unload(WASMModule *module);
/* 将module占用的空间释放 */

bool wasm_loader_find_block_addr(BlockAddr *block_addr_cache,
                            const uint8 *start_addr,
                            const uint8 *code_end_addr,
                            uint8 label_type,
                            uint8 **p_else_addr,
                            uint8 **p_end_addr,
                            char *error_buf,
                            uint32 error_buf_size);
/* 对于给定的block指令，找到对应的else,end地址，并缓存在BlockAddr*中。 */


WASMModule *wasm_loader_load_from_sections(WASMSection *section_list,
                               char *error_buf, uint32 error_buf_size);
/* 从WASMSection列表里载入 */
```

#### 2.5 wasm_runtime.c

##### 功能介绍

运行时

##### 对外接口

```c
WASMModule* wasm_load(const uint8 *buf, uint32 size,
          char *error_buf, uint32 error_buf_size);
/* 从buffer中载入模块，与wasm_loader接口相同 */

WASMModule*
wasm_load_from_sections(WASMSection *section_list,
                        char *error_buf, uint32_t error_buf_size);
/* 从section_list中载入模块，与wasm_loader接口相同 */

void
wasm_unload(WASMModule *module);
/* 回收载入的模块，与wasm_loader接口相同 */

WASMModuleInstance*
wasm_instantiate(WASMModule *module, bool is_sub_inst,
                 uint32 stack_size, uint32 heap_size,
                 char *error_buf, uint32 error_buf_size);
/* 实例化一个模块 */

void
wasm_deinstantiate(WASMModuleInstance *module_inst, bool is_sub_inst);
/* 回收一个模块实例 */

WASMFunctionInstance*
wasm_lookup_function(const WASMModuleInstance *module_inst,
                     const char *name, const char *signature);
/* 通过函数名，在export列表中查找对于函数 */

bool
wasm_call_function(WASMExecEnv *exec_env,
                   WASMFunctionInstance *function,
                   unsigned argc, uint32 argv[]);
/* 通过wasm_interp_call_wasm来调用函数实例，返回是否出现异常 */

bool
wasm_create_exec_env_and_call_function(WASMModuleInstance *module_inst,
                                       WASMFunctionInstance *func,
                                       unsigned argc, uint32 argv[]);
/* 创建运行时环境，并调用函数实例 */

void
wasm_set_exception(WASMModuleInstance *module_inst,
                   const char *exception);
/* 设置当前运行实例的异常信息 */

const char*
wasm_get_exception(WASMModuleInstance *module_inst);
/* 获取当前运行实例的异常信息 */

int32
wasm_module_malloc(WASMModuleInstance *module_inst, uint32 size,
                   void **p_native_addr);
/* 在该实例的运行环境中，分配size大小的空间 */

void
wasm_module_free(WASMModuleInstance *module_inst, int32 ptr);
/* 释放该实例申请的空间 */

int32
wasm_module_dup_data(WASMModuleInstance *module_inst,
                     const char *src, uint32 size);
/* 从src中复制char到新分配的空间 */

bool
wasm_validate_app_addr(WASMModuleInstance *module_inst,
                       int32 app_offset, uint32 size);
/* 检查应用程序地址的合法性 */

bool
wasm_validate_native_addr(WASMModuleInstance *module_inst,
                          void *native_ptr, uint32 size);
/* 检查原生地址的合法性 */

void *
wasm_addr_app_to_native(WASMModuleInstance *module_inst,
                        int32 app_offset);
/* 将应用程序地址转化为原生地址 */

int32
wasm_addr_native_to_app(WASMModuleInstance *module_inst,
                        void *native_ptr);
/* 将原生地址转化为应用程序地址 */

bool
wasm_get_app_addr_range(WASMModuleInstance *module_inst,
                        int32 app_offset,
                        int32 *p_app_start_offset,
                        int32 *p_app_end_offset);
/* 获取应用程序地址范围 */

bool
wasm_get_native_addr_range(WASMModuleInstance *module_inst,
                           uint8 *native_ptr,
                           uint8 **p_native_start_addr,
                           uint8 **p_native_end_addr);
/* 获取原生地址范围 */

bool
wasm_enlarge_memory(WASMModuleInstance *module, uint32 inc_page_count);
/* 尝试扩大内存 */

bool
wasm_call_indirect(WASMExecEnv *exec_env,
                   uint32_t element_indices,
                   uint32_t argc, uint32_t argv[]);
/* 通过给定Table中element的索引，间接调用函数 */
```

#### 2.6 platform_init.c

##### 功能介绍

初始化平台环境，目前接口为空函数。

##### 对外接口

```c
int
bh_platform_init()
{
    return 0;
}

void
bh_platform_destroy()
{
}
```

#### 2.7 bh_assert.h

##### 功能介绍

提供一个`assert`接口

##### 对外接口

```c
#define bh_assert(expr) bh_assert_internal((int)(uintptr_t)(expr), \
                                            __FILE__, __LINE__, #expr)

void bh_assert_internal(int v, const char *file_name, int line_number,
                        const char *expr_string);
/* assert (v != 0), 为0则输出错误信息并停止运行 */
```

#### 2.15 bh_log.h

##### 功能介绍

提供日志打印功能。

##### 对外接口

```C
void log_printf (const char* pFileName, unsigned int uiLine, const char* pFnucName, char *LogFmtBuf, ...);
/* 输出文件名、行数、函数名信息，并按照给定格式输出可变长参数 */
```

#### 2.16 bh_vector.h

##### 功能介绍

定义`Vector`数据结构，并提供基本接口。

##### 对外接口

```c
bool bh_vector_init(Vector *vector, uint32 init_length, uint32 size_elem);
/* 初始化vector，给定初始大小、元素大小 */

bool bh_vector_set(Vector *vector, uint32 index, const void *elem_buf);
/* 将第index位设置为*elem_buf */

bool bh_vector_get(const Vector *vector, uint32 index, void *elem_buf);
/* 获取第index位 */

bool bh_vector_insert(Vector *vector, uint32 index, const void *elem_buf);
/* 在第index位插入*elem_buf */

bool bh_vector_append(Vector *vector, const void *elem_buf);
/* 在末尾插入*elem_buf */

bool bh_vector_remove(Vector *vector, uint32 index, void *old_elem_buf);
/* 删掉第index位，并将原值存入old_elem_buf */

uint32 bh_vector_size(const Vector *vector);
/* 获取vector大小 */

bool bh_vector_destroy(Vector *vector);
/* 回收vecotr */
```

#### 2.17 posix_thread.c

##### 功能介绍

封装`pthread`接口，提供对thread,mutex,cond操作的接口。

##### 对外接口

```c
int os_thread_create_with_prio(korp_tid *tid, thread_start_routine_t start,
                               void *arg, unsigned int stack_size, int prio);

int os_thread_create(korp_tid *tid, thread_start_routine_t start, void *arg,
                     unsigned int stack_size);
/* 创建线程 */

korp_tid os_self_thread();
/* 获取当前线程 */

int os_mutex_init(korp_mutex *mutex);

int os_recursive_mutex_init(korp_mutex *mutex);

int os_mutex_destroy(korp_mutex *mutex);

int os_mutex_lock(korp_mutex *mutex);

int os_mutex_unlock(korp_mutex *mutex);
/* 对mutex的操作 */

int os_cond_init(korp_cond *cond);

int os_cond_destroy(korp_cond *cond);

int os_cond_wait(korp_cond *cond, korp_mutex *mutex);

int os_cond_reltimedwait(korp_cond *cond, korp_mutex *mutex, int useconds);

int os_cond_signal(korp_cond *cond);
/* 对条件变量的操作 */

int os_thread_join(korp_tid thread, void **value_ptr);
/* 线程join */

int os_thread_detach(korp_tid thread);

void os_thread_exit(void *retval);

uint8 *os_thread_get_stack_boundary();
/* 获取当前线程栈地址 */
```

#### 2.18 posix_time.c

##### 功能介绍

获取时间戳

##### 对外接口

```c
uint64 os_time_get_boot_microsecond();
/* 获取当前时间戳(ms) */
```

#### 2.19 wasm_memory.c

##### 功能介绍

提供内存管理相关接口供 `wasm_loader` 和 `wasm_runtime_common` 使用

##### 开放接口

```c
/* 初始化内存空间，需指定内存使用方式（池/分配器/系统分配器）
   mem_alloc_type 对应 (include/wasm_export.h):
     Alloc_With_Pool: 池模式，在用户定义的堆缓冲区中分配内存
     Alloc_With_Allocator: 用户自定义分配器模式，使用用户自定义分配器函数分配内存
     Alloc_With_System_Allocator: 系统分配器模式，使用系统分配器或平台的 `os_malloc` 函数
   alloc_option 为一个 union 结构
     池模式下指定缓冲区地址与大小 `heap_buf`, `heap_size`
     分配器模式下指定分配、重分配和释放函数 `malloc_func`, `realloc_func`, `free_func`
： */
bool
wasm_runtime_memory_init(mem_alloc_type_t mem_alloc_type,
                         const MemAllocOption *alloc_option);

/* 析构初始化过的内存空间，若不为池模式则只修改「已初始化」的标识位 */
void
wasm_runtime_memory_destroy();
```
