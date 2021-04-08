### 函数调用过程

![image-20210408162420802](C:\Users\xj\AppData\Roaming\Typora\typora-user-images\image-20210408162420802.png)


### 主要结构体

---

```
DeepStack(操作数栈)
DEEPInterpFrame(函数帧)
DEEPExecEnv(运行环境)
DEEPModule(从loader得到的module)
```
##### 头文件——"interp.h"

```c
//帧
struct DEEPInterpFrame {  //DEEP帧

    struct DEEPInterpFrame *prev_frame;//指向前一个帧

    struct DEEPFunction *function;//当前函数实例

    int *sp;  //操作数栈指针

} DEEPInterpFrame;

//操作数栈
typedef struct DeepStack{
    int capacity;//栈的最大容量
    int *sp;//操作数栈指针
    int *sp_end;//栈的上界
} DEEPStack;

//创建操作数栈
DeepStack stack_cons(){

    DeepStack stack;
    
    stack.capacity=100;
    
    stack.sp=(int*)malloc(sizeof(int));
    
    return stack;
}

//运行环境
typedef struct DEEPExecEnv {

    struct DEEPInterpFrame* cur_frame;//当前函数帧

    int *sp;//sp指针
    
    int *sp_end;//sp指针上界

} DEEPExecEnv;
```

### 主要函数

---

```
exec_instructions(执行代码块内指令)
call_main(为main函数创建帧，执行main函数里的指令)
```

### 代码主体

---

```c
#include "interp.h"
#include "loader.cpp"
#include "opcode.h"
using namespace std;

//执行代码块指令
void exec_instructions(DEEPExecEnv* env){
    int* sp = env->cur_frame->sp;
    char* ip = env->cur_frame->function->code_begin;
    char* ip_end = ip + env->cur_frame->function->code_size - 1;
    while(ip < ip_end){
        //提取指令码
        //立即数存在的话，提取指令码时提取立即数
        int opcode = (int)*ip;
        int temp1,temp2;
        switch(opcode){
            case DEEP_OP_END:
                ip++;
                break;

            case DEEP_OP_I32_ADD:
                ip++;
                temp1 = *(--sp);
                *(sp-1) += temp1;
                break;

            case DEEP_OP_I32_SUB:
                ip++;
                temp1 = *(--sp);
                *(sp-1) += temp1;
                break;

            case DEEP_OP_I32_MUL:
                ip++;
                temp1 = *(--sp);
                *(sp-1) *= temp1;
                break;

            case DEEP_OP_I32_DIV_U:
                ip++;
                temp1 = *(--sp);
                temp2 = *(--sp);
                if(temp2 != 0){
                    *(sp++) = temp1/temp2;
                }
                break;

            case DEEP_OP_I32_CONST:
                //读取立即数
                ip++;
                int temp = read_leb_u32(&ip);
                //temp入栈
                *(sp++) = temp;
                break;
        }
        
        //检查操作数栈是否溢出
        if(sp > env->sp_end){
            printf("%s","warning! Operand stack overflow!");
            break;
        }
        
    }
    //更新env
    env->sp=sp;
}

//为main函数创建帧，执行main函数
int call_main(DEEPExecEnv* current_env, DEEPModule* module){

    //从module中取出main函数所在的DEEPFunction
    DEEPFunction* main_func = module->func_section[start_index];//module.start_index记录了main函数索引

    //为main函数创建帧
    struct DEEPInterpFrame frame;
    //初始化
    frame.sp = current_env->sp;
    frame.function = main_func;

    //更新env中当前帧
    current_env->cur_frame = &frame;

    //执行frame中函数
    //sp要下移，栈顶元素即为函数参数
    exec_instructions(current_env);

    //返回栈顶元素
    return  *(current_env->sp-1);
}

int main() {
    //创建操作数栈
    DeepStack stack = stack_cons();

    //先声明环境并初始化
    DEEPExecEnv deep_env;
    DEEPExecEnv* current_env=&deep_env;
    current_env->sp=stack.sp;

    //创建module，简单加减乘除只用到一个module
    DEEPModule* module = loader();//从loader中获取module

    int ans = call_main(current_env,module);

    printf("%d",ans);

}
```

##### 头文件——"opcode.h"

```c
enum DEEPOpcode {
    DEEP_OP_END           = 0x0b, //end

    DEEP_OP_GET_LOCAL     = 0x20, //get_local
    DEEP_OP_SET_LOCAL     = 0x21, //set_local
    DEEP_OP_TEE_LOCAL     = 0x22, //tee_local

    DEEP_OP_I32_CONST     = 0x41, // i32.const

    DEEP_OP_I32_ADD       = 0x6a, // i32.add
    DEEP_OP_I32_SUB       = 0x6b, // i32.sub
    DEEP_OP_I32_MUL       = 0x6c, // i32.mul
    DEEP_OP_I32_DIV_S     = 0x6d, // i32.div_s
    DEEP_OP_I32_DIV_U     = 0x6e, // i32.div_u
};
```



### 下一步计划

---

1. 与loader合作完成更多段的解析，实现更复杂函数的解释

2. 丰富结构体内容，使其支持更多的指令集操作

3. 在现有基础上实现部分异常检查

   

