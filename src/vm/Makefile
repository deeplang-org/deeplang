# 指令编译器和选项
CC=gcc
CFLAGS=-Wall -std=gnu99
 
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
	   runtime_timer.c\
	   posix_time.c\
	   posix_thread.c\
	   posix_memmap.c\
	   posix_malloc.c\
	   platform_init.c\
	   mem_alloc.c\
	   deep_wasm_main.c \
	   invokeNative_general.c\
	   ems_kfc.c\
	   ems_alloc.c\
	   bh_vector.c\
	   bh_read_file.c\
	   bh_list.c\
	   bh_log.c\
	   bh_common.c\
	   bh_assert.c
INC = -I./include
OBJS = $(SRCS:.c=.o)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ -lpthread -lm
 
clean:
	rm -rf $(TARGET) $(OBJS)
 
%.o:%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c -g $<
