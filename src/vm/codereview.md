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
| bh_hashmap.c           | 闭地址法实现的哈希表，使用 os_malloc，找不到使用的地方。 |
| bh_list.c              |                                                              |
| bh_log.c               | 日志系统，包括debug、dump等，已经自研了。                    |
| bh_queue.c             |                                                              |
| bh_read_file.c         |                                                              |
| bh_vector.c            | 提供vector的实现与操作接口。                                 |
| ems_alloc.c            | 内存分配、重分配、释放等实现。 |
| ems_kfc.c              | 内存池定义、构造、析构、移动、状态查询相关接口。 |
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

#### 2.20 wasm_exec_env.{c / h}

##### 功能介绍

##### 数据结构定义

```c
/* 运行环境 Execution Environment
 * 存储当前线程的 WASM 模块实例地址
 * 有可开启的线程管理相关字段
 */
typedef struct WASMExecEnv {
    /* 前序、后继线程的运行环境指针 */
    struct WASMExecEnv *next;
    struct WASMExecEnv *prev;

    /* 存储原生栈边界地址以检查栈溢出 */
    uint8 *native_stack_boundary;

    /* The WASM module instance of current thread */
    struct WASMModuleInstanceCommon *module_inst;

    /* Aux stack boundary */
    uint32 aux_stack_boundary;

    /* attachment for native function 原生 API 函数的指针？ */
    void *attachment;

    /* 用户态数据？ */
    void *user_data;

    /* Current interpreter frame of current thread */
    struct WASMInterpFrame *cur_frame;

    /* The native thread handle of current thread
     * `typedef pthread_t korp_tid;` in platform_internal.h */
    korp_tid handle;

#if WASM_ENABLE_INTERP != 0
    BlockAddr block_addr_cache[BLOCK_ADDR_CACHE_SIZE][BLOCK_ADDR_CONFLICT_SIZE];
#endif

    /* 疑似硬件边界检查相关代码 */
#ifdef OS_ENABLE_HW_BOUND_CHECK
    WASMJmpBuf *jmpbuf_stack_top;
#endif

    /* The WASM stack size */
    uint32 wasm_stack_size;

    /* The WASM stack of current thread */
    union {
        /* 使整个 union 八字节对齐 */
        uint64 __make_it_8_byte_aligned_;

        struct {
            /* The top boundary of the stack
             * top - bottom 可得到栈空间大小 */
            uint8 *top_boundary;

            /* Top cell index which is free. */
            uint8 *top;

            /* The WASM stack. 必须为 struct WASMExecEnv 最后一个域 */
            uint8 bottom[1];
        } s;
    } wasm_stack;
} WASMExecEnv;
```

##### 开放接口

```c
/* 内部辅助函数
 * 创建运行环境实例
 * 分配栈空间并清零
 * 元信息 + 栈空间总大小不可超过 4 GB (UINT32_MAX Bytes)
 */
WASMExecEnv *
wasm_exec_env_create_internal(struct WASMModuleInstanceCommon *module_inst,
                              uint32 stack_size);

/* 内部辅助函数
 * 销毁已分配运行环境实例
 * 有硬件边界检查时会进行额外操作：（具体？）
 */
void
wasm_exec_env_destroy_internal(WASMExecEnv *exec_env);

/*
 *
 */
WASMExecEnv *
wasm_exec_env_create(struct WASMModuleInstanceCommon *module_inst,
                     uint32 stack_size);

void
wasm_exec_env_destroy(WASMExecEnv *exec_env);

/* 在 WASM 栈上分配一帧，大小必须是 4 字节的倍数
 * 直接修改当前运行环境的栈的顶部空内存位地址
 * 检测分配是否会导致栈溢出，若有可能则返回 NULL，不进行分配。
 * outs area 是什么…？The outs area size cannot be larger than the frame size?
 */
static inline void *
wasm_exec_env_alloc_wasm_frame(WASMExecEnv *exec_env, unsigned size);

/* 回收栈帧空间，需给定当前运行环境和上一帧顶部的下一个紧邻的地址（指向空内存） */
static inline void
wasm_exec_env_free_wasm_frame(WASMExecEnv *exec_env, void *prev_top);

/* 获取当前 WASM 栈的顶部指针，即下一个可用的空内存地址 */
static inline void*
wasm_exec_env_wasm_stack_top(WASMExecEnv *exec_env);

static inline void
wasm_exec_env_set_cur_frame(WASMExecEnv *exec_env,
                            struct WASMInterpFrame *frame);

/* 获取当前帧指针 */
static inline struct WASMInterpFrame*
wasm_exec_env_get_cur_frame(WASMExecEnv *exec_env);

/* Get the WASM module instance of current thread */
struct WASMModuleInstanceCommon *
wasm_exec_env_get_module_inst(WASMExecEnv *exec_env);

/* set thread handle and stack boundary with current thread */
void
wasm_exec_env_set_thread_info(WASMExecEnv *exec_env);

#ifdef OS_ENABLE_HW_BOUND_CHECK
void
wasm_exec_env_push_jmpbuf(WASMExecEnv *exec_env, WASMJmpBuf *jmpbuf);

WASMJmpBuf *
wasm_exec_env_pop_jmpbuf(WASMExecEnv *exec_env);
#endif
```

#### 2.21 ems_kfc.c / ems_alloc.c / ems_gc.h

- HMU: Heap Memory Unit
- KFC: K Free Chunk?

##### 数据结构

```c
typedef uint32 gc_uint32;

/**
 * bit offset 30 - 31: indicating HMU status.
 *   01 being HMU_FC (free), 10 being HMU_VO (allocated)
 * bit offset 29: P in use bit means the previous chunk is in use.
 *   1 being in use, 0 being free.
 * bit offset 28: VO_FB (VO_free block).
 *   1 being freed.
 * bit offset 0 - 27: HMU size.
 *   The hmu size is divisible by 8, its lowest 3 bits are 0, so we only
 *   store its higher bits of bit [29..3], and bit [2..0] are not stored.
 *   After that, the maximal heap size can be enlarged from (1<<27) B = 128MB
 *   to (1<<27) * 8 B = 1GB.
 **/
typedef struct hmu_struct {
    gc_uint32 header;
} hmu_t;

typedef struct hmu_normal_node {
    hmu_t hmu_header;
    gc_int32 next_offset;
} hmu_normal_node_t;

typedef struct gc_heap_struct {
    /* for double checking*/
    gc_handle_t heap_id;

    gc_uint8 *base_addr;
    gc_size_t current_size;

    korp_mutex lock;

    hmu_normal_node_t kfc_normal_list[HMU_NORMAL_NODE_CNT];

    /* order in kfc_tree is: size[left] <= size[cur] < size[right] */
    hmu_tree_node_t kfc_tree_root;

    gc_size_t init_size;
    /* 历史最大堆占用 in bytes */
    gc_size_t highmark_size;
    gc_size_t total_free_size;
} gc_heap_t;

#define HMU_NORMAL_NODE_CNT 32
#define HMU_FC_NORMAL_MAX_SIZE ((HMU_NORMAL_NODE_CNT - 1) << 3)
#define HMU_IS_FC_NORMAL(size) ((size) < HMU_FC_NORMAL_MAX_SIZE)
#if HMU_FC_NORMAL_MAX_SIZE >= GC_MAX_HEAP_SIZE
#error "Too small GC_MAX_HEAP_SIZE"
#endif
```

##### 开放接口

```c
/**
 * GC initialization from a buffer
 *
 * @param buf the buffer to be initialized to a heap
 * @param buf_size the size of buffer, >= 1024 bytes
 *
 * @return gc handle if success, NULL otherwise
 *
 * 返回的地址保证是 8 的倍数（即内存为8字节对齐，参考 buf_aligned
 *
 */
gc_handle_t
gc_init_with_pool(char *buf, gc_size_t buf_size);

/**
 * Destroy heap which is initilized from a buffer
 *
 * @param handle handle to heap needed destroy
 *
 * @return GC_SUCCESS if success
 *         GC_ERROR for bad parameters or failed system resource freeing.
 */
int
gc_destroy_with_pool(gc_handle_t handle);

/**
 * Migrate heap from one place to another place
 * Used to enlarge memeory.
 * Traverse through the kfc_tree, adjust all pointers with calculated offset.
 *
 * @param handle handle of the new heap
 * @param handle_old handle of the old heap
 *
 * @return GC_SUCCESS if success, GC_ERROR otherwise
 */
int
gc_migrate(gc_handle_t handle, gc_handle_t handle_old);

/**
 * Re-initialize lock of heap
 *
 * @param handle the heap handle
 *
 * @return GC_SUCCESS if success, GC_ERROR otherwise
 */
int
gc_reinit_lock(gc_handle_t handle);

/**
 * Destroy lock of heap
 *
 * @param handle the heap handle
 */
void
gc_destroy_lock(gc_handle_t handle);

/**
 * Get Heap Stats
 *
 * @param stats [out] integer array to save heap stats
 * @param size [in] the size of stats
 * @param mmt [in] type of heap, MMT_SHARED or MMT_INSTANCE
 */
void *
gc_heap_stats(void *heap, uint32* stats, int size);

#if BH_ENABLE_GC_VERIFY == 0

/**
 * Allocate some memory, convert it to `gc_object_t` and return
 * The returned address will omit `hmu_t.header` (i.e., base address + 1)
 * The allocated trunk is 8 bytes aligned,
 * the buffer appended due to alignment will be cleared.
 * HMU's head will be set to HMU_VO status, and unfree_vo will be set
 *   ( in header, bit offset 31, 30, 29, 28 will be `10_0`,
 *     where 29 remain untouched )
 *
 * For Finding a proper HMU with given size ( `alloc_hmu_ex` -> `alloc_hmu` )
 *
 * @param size should cover the header and should be 8 bytes aligned
 *
 * Note: This function will try several ways to satisfy the allocation request:
 *   1. Find a proper on available HMUs.
 *   2. GC will be triggered if 1 failed.
 *   3. Find a proper on available HMUS.
 *   4. Return NULL if 3 failed
 *
 * In current implementation, only 1 will be performed. ( `alloc_hmu` )
 *   - GC will not be performed here.
 *   - Heap extension will not be performed here.
 *
 * 1. Allocate from normal ...
 * 2. Allocate from reused tree node
 *   - Find the smallest node with size ≥ then required size
 *     by find the rightmost node with size ≥ required, then try left child
 *   - If the remaining space cut from the free node found is big enough to
 *     be a stand-alone free chunk, split it out and initialise into a free
 *     trunk, add back to heap. Otherwise, return the whole trunk without
 *     splitting.
 *   - Mark the `P in use` flag for the next trunk (in terms of address)
 *   - update total free size
 *   - update highmark size
 */
 **/
gc_object_t
gc_alloc_vo(void *heap, gc_size_t size);

gc_object_t
gc_realloc_vo(void *heap, void *ptr, gc_size_t size);

int
gc_free_vo(void *heap, gc_object_t obj);

#else /* else of BH_ENABLE_GC_VERIFY */

gc_object_t
gc_alloc_vo_internal(void *heap, gc_size_t size,
                     const char *file, int line);

gc_object_t
gc_realloc_vo_internal(void *heap, void *ptr, gc_size_t size,
                       const char *file, int line);

/**
 * Return GC_ERROR when trying to free a freed block
 * Return GC_SUCCESS otherwise, including NULL pointer
 * Check for one block above and one block below,
 *   Merge if any of consecutive block is free as well.
 **/
int
gc_free_vo_internal(void *heap, gc_object_t obj,
                    const char *file, int line);

#define gc_alloc_vo(heap, size) \
    gc_alloc_vo_internal(heap, size, __FILE__, __LINE__)

#define gc_realloc_vo(heap, ptr, size) \
    gc_realloc_vo_internal(heap, ptr, size, __FILE__, __LINE__)

#define gc_free_vo(heap, obj) \
    gc_free_vo_internal(heap, obj, __FILE__, __LINE__)

#endif /* end of BH_ENABLE_GC_VERIFY */
```

##### 内部二叉查找树实现

- 左 < 中 < 右，按 HMU Size 顺序
- 无自平衡机制
- 支持任意位置删除节点
- 查询最小的 ≥ 某阈值节点：
  - 向右子树遍历直到找到 ≥ 阈值的节点
  - 然后向左子树遍历，找到最后一个满足条件的节点

#### 2.22 runtime_timer.c

##### 开放接口

未使用的开放接口。

```c
timer_ctx_t create_timer_ctx(timer_callback_f timer_handler,
                             check_timer_expiry_f, int prealloc_num,
                             unsigned int owner);
void destroy_timer_ctx(timer_ctx_t);
unsigned int timer_ctx_get_owner(timer_ctx_t ctx);

uint32 sys_create_timer(timer_ctx_t ctx, int interval, bool is_period,
                        bool auto_start);
bool sys_timer_destroy(timer_ctx_t ctx, uint32 timer_id);
bool sys_timer_cancel(timer_ctx_t ctx, uint32 timer_id);
bool sys_timer_restart(timer_ctx_t ctx, uint32 timer_id, int interval);
void cleanup_app_timers(timer_ctx_t ctx);
int check_app_timers(timer_ctx_t ctx);
int get_expiry_ms(timer_ctx_t ctx);
```

#### 2.23 bh_hashmap.c

闭地址法实现的线性哈希表。

##### 数据结构

```C
typedef struct HashMapElem {
    void *key;
    void *value;
    struct HashMapElem *next; /* 相同 hash key 的下一个元素 */
} HashMapElem;

struct HashMap {
    /* size of element array */
    uint32 size;
    /* lock for elements */
    korp_mutex *lock;
    /* hash function of key */
    HashFunc hash_func;
    /* key equal function */
    KeyEqualFunc key_equal_func;
    KeyDestroyFunc key_destroy_func;
    ValueDestroyFunc value_destroy_func;
    HashMapElem *elements[1]; /* 应当是语法糖，具体大小会在创建时动态分配 */
};

/* Maximum initial size of hash map */
#define HASH_MAP_MAX_SIZE 65536

/* Hash function: to get the hash value of key. */
typedef uint32 (*HashFunc)(const void *key);

/* Key equal function: to check whether two keys are equal. */
typedef bool (*KeyEqualFunc)(void *key1, void *key2);

/* Key destroy function: to destroy the key, auto called
   when an hash element is removed. */
typedef void (*KeyDestroyFunc)(void *key);

/* Value destroy function: to destroy the value, auto called
   when an hash element is removed. */
typedef void (*ValueDestroyFunc)(void *key);
```

##### 开放接口

```C
/* Return NULL on failure */
HashMap*
bh_hash_map_create(uint32 size, bool use_lock,
                   HashFunc hash_func,
                   KeyEqualFunc key_equal_func,
                   KeyDestroyFunc key_destroy_func,
                   ValueDestroyFunc value_destroy_func);

/**
 * Note: fail if key is NULL or duplicated key exists in the hash map,
 */
bool
bh_hash_map_insert(HashMap *map, void *key, void *value);

/* Return NULL on failure */
void*
bh_hash_map_find(HashMap *map, void *key);

/**
 * Note: the old key and old value won't be destroyed by key destroy
 *       function and value destroy function, they will be copied to
 *       p_old_key and p_old_value for user to process.
 */
bool
bh_hash_map_update(HashMap *map, void *key, void *value,
                   void **p_old_value);

/**
 * Note: the old key and old value won't be destroyed by key destroy
 *       function and value destroy function, they will be copied to
 *       p_old_key and p_old_value for user to process.
 */
bool
bh_hash_map_remove(HashMap *map, void *key,
                   void **p_old_key, void **p_old_value);

/**
 * Note: the key destroy function and value destroy function will be
 *       called to destroy each element's key and value if they are
 *       not NULL.
 */
bool
bh_hash_map_destroy(HashMap *map);
```
