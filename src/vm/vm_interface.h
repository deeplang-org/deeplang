//
// Created by 杨文章 on 2020/10/21.
//

#ifndef DEEPLANG_VM_INTERFACE_H
#define DEEPLANG_VM_INTERFACE_H
#include "include/platform_common.h"

#ifdef __cplusplus
extern "C"
{
#endif

int deep_wasm_vm_init(void);
int deep_wasm_eval(uint8* wasm_buf, uint32 wasm_size);

#ifdef __cplusplus
};
#endif



#endif //DEEPLANG_VM_INTERFACE_H
