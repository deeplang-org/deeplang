## wasmvm building

### 1.ENV

**操作系统**：Windows10

**CPU**：X86_64ENV

**运行环境**：msys2

**编译器**：gcc  9.3.0

**Make**：GNU Make 4.3

**step1.install tools**

```txt
$ pacman -Syu
$ pacman -S gcc
$ pacman -S make
```

**step2.version**

```txt
Eric@USER-20171230HD MINGW64 /e/github/deeplang/src/vm
$ gcc -v
使用内建 specs。
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-pc-msys/9.3.0/lto-wrapper.exe
...
线程模型：posix
gcc 版本 9.3.0 (GCC)

Eric@USER-20171230HD MINGW64 /e/github/deeplang/src/vm
$ make -v
GNU Make 4.3
...
```



### 2.compiling

**step1. make clean**

```txt
Eric@USER-20171230HD MINGW64 /e/github/deeplang/src/vm
$ make clean
rm -rf wasmvm wasm_c_api.o wasm_exec_env.o wasm_interp_classic.o wasm_loader.o wasm_memory.o wasm_native.o wasm_runtime.o wasm_runtime_common.o runtime_timer.o posix_time.o posix_thread.o posix_memmap.o posix_malloc.o platform_init.o mem_alloc.o main.o invokeNative_general.o ems_kfc.o ems_hmu.o ems_alloc.o bh_vector.o bh_read_file.o bh_list.o bh_log.o bh_common.o bh_assert.o
```

**step2. make**

```txt
Eric@USER-20171230HD MINGW64 /e/github/deeplang/src/vm
$ make
gcc -Wall -std=gnu99 -I./include -o wasm_c_api.o -c -g wasm_c_api.c
gcc -Wall -std=gnu99 -I./include -o wasm_exec_env.o -c -g wasm_exec_env.c
gcc -Wall -std=gnu99 -I./include -o wasm_interp_classic.o -c -g wasm_interp_classic.c
...
gcc -Wall -std=gnu99 -I./include -o bh_assert.o -c -g bh_assert.c
gcc -o wasmvm wasm_c_api.o wasm_exec_env.o wasm_interp_classic.o wasm_loader.o wasm_memory.o wasm_native.o wasm_runtime.o wasm_runtime_common.o runtime_timer.o posix_time.o posix_thread.o posix_memmap.o posix_malloc.o platform_init.o mem_alloc.o main.o invokeNative_general.o ems_kfc.o ems_hmu.o ems_alloc.o bh_vector.o bh_read_file.o bh_list.o bh_log.o bh_common.o bh_assert.o
```

- If you need to assign a specific compiler version, use `make -e CC=<compiler path>`

**step3. run**

```
Eric@USER-20171230HD MINGW64 /e/github/deeplang/src/vm
$ ./wasmvm.exe hellodeeplang.wasm
main.c:62, main(), BUILD_TARGET_X86_64
wasm_runtime.c:1101, wasm_instantiate(), [data_seg]: length = 16 (0x10)

    0x800048634  68 65 6C 6C 6F 20 64 65 - 65 70 6C 61 6E 67 0D 00         | hello deeplang..

wasm_runtime.c:1152, wasm_instantiate(), [memory_data]: length = 64 (0x40)

    0x1004306b8  00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00         | ................
    0x1004306c8  68 65 6C 6C 6F 20 64 65 - 65 70 6C 61 6E 67 0D 00         | hello deeplang..
    0x1004306d8  00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00         | ................
    0x1004306e8  00 00 00 00 00 00 00 00 - 00 00 00 00 00 00 00 00         | ................

wasm_runtime_common.c:2684, wasm_runtime_invoke_native(), signature:($)i
hello deeplang
```

最后一行是运行结果（`hello deeplang`），其他为调试信息。
