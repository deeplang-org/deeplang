# 指令编译器和选项
CC=gcc
CFLAGS=-Wall -std=gnu99
DEFS=-DWASM_ENABLE_LIBC_BUILTIN=1 -DWAMR_BUILD_INTERP=1 -DWASM_ENABLE_LIBC_WASI=1 -DWAMR_BUILD_LIBC_WASI=1 -DWAMR_BUILD_FAST_INTERP=1 -DWASM_ENABLE_INTERP=1 -DWASM_ENABLE_AOT=0 -DWASM_ENABLE_JIT=0 -DWASM_ENABLE_FAST_INTERP=0
CFLAGS += $(DEFS)
# 目标文件
TARGET=wasmvm
SRCS = wasm_c_api.c\
	   wasm_exec_env.c\
	   wasm_interp_classic.c\
	   wasm_loader.c\
	   wasm_memory.c\
	   wasm_native.c\
	   wasm_runtime.c\
	   wasm_runtime_common.c\
	   math.c\
	   runtime_timer.c\
	   posix.c\
	   posix_time.c\
	   posix_thread.c\
	   posix_memmap.c\
	   posix_malloc.c\
	   platform_init.c\
	   mem_alloc.c\
	   main.c \
	   invokeNative_general.c\
	   ems_kfc.c\
	   ems_hmu.c\
	   ems_alloc.c\
	   bh_vector.c\
	   bh_read_file.c\
	   bh_list.c\
	   bh_log.c\
	   bh_common.c\
	   bh_assert.c\
	   random.c\
	   str.c\
	   libc_wasi_wrapper.c\
	   libc_builtin_wrapper.c

INC = -I./include
OBJS = $(SRCS:.c=.o)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ -lpthread
 
clean:
	rm -rf $(TARGET) $(OBJS)
 
%.o:%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c -g $<
