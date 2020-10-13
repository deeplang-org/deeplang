<a href = "https://github.com/thomasyonug/deeplang">
<img width = "90%" height = "auto" src = "https://raw.githubusercontent.com/thomasyonug/deeplang/develop/assets/banner.jpg" alt = "The Deep Programming Language">
</a>


deeplang语言是一种自制编程语言，由来自浙大和中科大的同学共同完成。
   
我们致力于将deeplang语言打造为具有鲜明内存安全特性的面向IoT场景的语言，设计过程中参考Rust的安全机制，但又根据IoT场景的特性选择了更合适的解释执行的模式。这是一种静态类型、强类型语言，按照C-style设计语法，同时支持面向对象、过程式和逻辑式的混合范式。
   
deeplang的独特安全特性帮助其具有一定的竞争力。作者正在持续的开发和迭代中。


---
# How to build

``` bash
$ git submodule update --init --recursive
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
```
---
# 目录
1. [注释](#注释)
1. [程序入口](#程序入口)
1. [控制语句](#控制语句)
1. [函数定义](#函数定义)
1. [变量定义](#变量定义)
1. [类与接口](#类与接口)
1. [表达式](#表达式)
1. [基础类型](#基础类型)


# 注释
单行注释
``` dp
// code
```
多行注释
``` dp
/*
code
code
*/
```

# 程序入口
在deeplang程序中，顶层代码没有表达式，只有各类定义。

比如类，函数，变量等：
``` dp
class Foo {};

fun bar() -> () {};

let a: Int = 1;
```
整个程序的入口有且只有一个，就是以main作为名字的函数。

# 控制语句
条件控制语句
``` dp
let t: Bool = true;

if (t) {
    foo();
} else {
    bar();
};
```
循环控制语句，与流行语言不通，deeplang中的for语句初始化需要用花括号包裹

所定义的变量生命周期在退出for循环后结束
``` dp
for ({let i: Int = 0}; i < 10, i++) {
    foo();
};
```

# 变量定义
以let定义的变量是常量，letmut定义的变量是可变的。
``` dp
let foo: Int = 1;
let mut bar: Int = 1;

foo = 2; // illegal
bar = 2;
```

# 函数
## 签名与定义
函数签名分为两个部分，一个是参数类型，一个是返回值类型

``` dp
fun foo(bar: Bar) -> Foo {};
```

如果是多参数函数，以逗号分隔参数
``` dp
fun multiParam(x: i32, y: i32) {};
```

# 类与接口
## 类定义
在deeplang中，一个class可以单继承，也可以impl多个interface。

每个类定义中，都需要定义一个构造函数，即constructor。

在类体内部的代码都要求写访问控制权限，目前只提供public，private两种访问控制操作。

``` dp
class Foo extends Bar impl Foo1, Foo2 {
    constructor() {};

    private fun foo1(bar: Bar, foo: Foo) {
        
    };

    public let foo2: i32;
    
};
```

## 接口定义
interface的定义与class类似，也可以单继承interface。

interface体内只有声明，不能有具体的定义。

``` dp
interface Foo {};

interface Bar extends Foo {
    public let a: i32;
    private fun b(Bar) -> ();
};
```

## 实例化class
可以使用new操作符来实例化一个class, 并且可以使用point操作符来访问实例中的方法和属性。
``` dp
let foo: Foo = new Foo();

foo.bar();
```

# 表达式
## 常量表达式
目前deeplang中有两种常量表达式
1. Int
2. String
``` dp
let i: Int = 1;
let s: String = "str";
```
## 算术，逻辑，一元表达式
``` dp
1 + 1;
2 * 2;
3 - 3;
4 / 4;
5 < 6;
7 == 7;
9 > 8;

5 >> 1;
5 << 1;

let foo: Bool = true;

false == !foo;

```

## 宏调用表达式
目前deeplang不支持自定义宏，并只提供builtin的数组方法宏，可以用来简化数组操作

宏调用以 @ 操作符开始，后跟调用的宏名
``` dp
let arr: [Int] = [];
arr@match([s] == 1, [s + 10] == 1);
```

# 基础类型
## 基本类型
``` dp
object
    bool
    tuple                // empty tuple alias DPUnit type
    i8, i16, i32, i64
    u8, u16, u32, u64
    f32, f64
    char                 // 16bit
    array: [T; N]        // T is a parameter type, N is length
    list: [T]
    lambda: ->
```
## 数组
数组作为一种builtin的参数化类型，可以与其他类型结合实例化(proposed)
比如array和i32，那么类型表达式就是 [i32; 10]
``` dp
let arr: [i32;10] = [];
```






