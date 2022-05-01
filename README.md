<a href = "https://github.com/deeplang-org/deeplang">
<img width = "90%" height = "auto" src = "./assets/banner.jpg" alt = "Deeplang: a new programming language for IoT">
</a>

# Deeplang 简介

Deeplang语言是一种自制编程语言，由来自浙大、中科大、帝国理工等高校的学生共同完成。

我们致力于将Deeplang语言打造为具有鲜明内存安全特性的面向IoT场景的语言，设计过程中参考Rust的安全机制，但又根据IoT场景的特性选择了更合适的解释执行模式。Deeplang是一种静态类型、强类型语言，参考C-style设计语法，同时支持过程式、逻辑式和函数式的混合范式。

Deeplang的独特安全特性帮助其具有一定的竞争力。作者正在持续的开发和迭代中。

---

## 目录

1. [注释](#注释)
1. [程序入口](#程序入口)
1. [表达式](#表达式)
1. [控制语句](#控制语句)
1. [模式匹配](#模式匹配)
1. [函数](#函数)
1. [内建类型](#内建类型)
1. [类型定义](#类型定义)
1. [接口声明](#接口实现)
1. [接口实现](#接口实现)
1. [命名规范总结](#命名规范总结)
1. [仍在设计中的特性](#仍在设计中的特性)

## 注释

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

## 程序入口

在Deeplang程序中，顶层代码没有表达式，只有各类定义。
具体来说，Deeplang有如下的顶层代码：

- 类型定义
- 接口声明
- 接口实现
- 全局变量定义
- 函数定义

整个程序的运行入口有且只有一个，就是以main作为名字的函数。

## 表达式

Deeplang和C、Java等语言一样，采用了表达式和语句二分的设计。

Deeplang中有以下几种表达式：

- 字面量，包括整数、浮点数、单个字符和字符串
- 变量名字。变量名字必须以小写字母开头。
- 一元操作符和二元操作符，如`! x`、`1 + 2`等。
- 元组，如`(1, "2", (3, 4))`
- 数组，如`[1, 1, 4, 5, 1, 4]`
- 代数数据类型（和类型），形如`<分支名字>(<值列表>)`。详见[类型定义的部分](#类型定义)。
- 创建结构体，形如是`<类型名字> { <域名字>: <值>, ... }`。
- 获取结构体中的域，如`point.x`。
- 函数调用，形如`<函数名字>(<参数列表>)`。
- 调用方法，形如`<表达式>.<方法名字>(<参数列表>)`。Deeplang中没有类系统，方法调用的解析是静态的。多态可以通过接口实现。
- 表达式层级的条件。语法待定。
- 表达式层级的模式匹配。语法待定。

## 控制语句

Deeplang中有以下的控制语句：

- 每个表达式都是控制语句。表达式的结果会被丢弃。
- 可以将多条控制语句有分号连接、用花括号括起，按顺序执行，变成一条语句。
- 声明变量`let <pattern> [= <rhs>]`。其中`<pattern>`是一个**带类型标注的**[模式](#模式匹配)，`<rhs>`是一个表达式。通过支持等于号左侧出现任意pattern，可以实现如`let (x, y) = some_pair`的便利解构。
- 条件语句`if (<条件>) <分支1> else <分支2>`。
- 基于迭代器的for循环，如：

  ```Deeplang
          for (<pattern> : iterable) {
              ...
          }
  ```

  这类for循环的具体语义取决于（尚未完成的）标准库中的迭代器设计。
- while循环，形如：

  ```Deeplang
          while (<循环继续条件，表达式>)
            <循环体，必要时由花括号括起>
  ```

- 模式匹配语句，例如：

  ```Deeplang
        match (optional_integer) {
            Some(x) => { return x }
            None    => { return 0 }
        }
  ```

- 特殊控制语句，如`return`，`break`和`continue`。

## 模式匹配

Deeplang中支持一套模式匹配系统，包括如下几种可以用于匹配的模式：

- 下划线`_`，匹配任何值。
- 变量`[mut] <变量名> [: <类型>]`，匹配任何值，并将`<变量名>`绑定到匹配到的值。新的变量默认是不可变的，除非在变量名前加上`mut`前缀。
- `as`模式，形如如`<pattern> as [mut] <variable> [: <类型]`。如果匹配的值能够与`<pattern>`匹配，将`<variable>`绑定到该值。`variable`同样可以用`mut`修饰。
- ADT模式，如`None`，`Some(x)`，`Some(Some(y))`等。
- 结构体模式，形如`<类型名字> { <结构体的域> : <匹配这个域的值的模式>, ... }`。不需要匹配所有的域，没有在模式中出现的域将被无视。
- 元组解包模式，如`(a, (b, c), d)`等。

## 函数

函数的签名形如`fun <函数名字>(<参数列表>) -> <返回值类型>`，其中参数列表用逗号隔开。目前参数类型和返回值类型都必须显式标注。一些函数定义的例子如下：

```dp
fun foo(bar: Bar) -> Foo {
   ...
}
```

```dp
fun multiParam(x: i32, y: i32) {
    ...
}
```

## 内建类型

Deeplang中有如下的内建类型：

```Deeplang
Bool
(...)                // tuple type
()                   // empty tuple alias Unit type
I8, I16, I32, I64
U8, U16, U32, U64
F32, F64
Char                 // 16bit
[T; N]               // T-array of length N
```

暂时还没有List的类型。

## 自定义类型

Deeplang中支持两种自定义类型：结构体和代数数据类型(ADT)。Deeplang中类型名字必须以大写字母开头。

### 结构体类型定义

```Deeplang
type <类型名字> {
    <域名字> : <域类型>,
    ...
}
```

结构体的域的名字都必须以小写字母开头。

使用结构体定义新类型的一些例子如下：

```Deeplang
type Color {
    r : U8,
    g : U8,
    b : U8
}
```

```Deeplang
type Point {
    x : F32,
    y : F32,
    z : F32
}
```

此外，结构体定义还支持委托。在结构体类型的声明中，可以加入形如`as <域名字> : <委托的类型>`的声明。

例如，在声明：

```Deeplang
type S2 {
    as s1 : S1
}
```

中，类型`S2`会有一个名为`s1`、类型为`S1`的域。此外，`S1`中的所有域都将被“委托”到`S2`中。也就是说，对于`S1`中的每一个域`x`，
`S2`中也会有一个对应的域`x`，且`S2.x = S2.s1.x`。

下面的例子展示了委托的使用方法：

```Deeplang
type ColoredPoint {
    as position : Point,
    color : Color
}
```

```Deeplang
let cp : ColoredPoint = ...;
cp.color;     // of type Color
cp.position;  // of type Point
cp.x          // of type F32, same as cp.position.x
```

### ADT类型定义

```Deeplang
type <类型名字> [
    <分支名字>[(<类型参数列表>)],
    ...
]
```

每个ADT必须有至少一个分支，而每个分支的参数类型列表是可选的。如果没有参数，则不写`()`。

ADT中分支的名字必须以大写字母开头。分支的类型参数列表中，可以给参数加上名字。但这些名字只有注释作用，没有实际语义。

使用ADT定义新类型的一个例子如下：

```Deeplang
type Shape [
    Rectangle(width : U32, height : U32),
    Circle(radius : U32),
    Nothing
]
```

可以通过模式匹配来对一个ADT值的不同分支作出不同的处理。

## 接口声明

在Deeplang中，方法调用的解析是静态的，多态需要通过接口来实现的。

接口声明形如：

```Deeplang
interface <接口名字> extends <依赖的接口列表> {
    fun <方法名字>(参数列表) -> <返回值类型>;
    ...
}
```

通过为一个类型实现该接口，可以使该类型的值支持接口中的方法的调用。在接口声明内部，可以通过`This`来指代实现该接口的类型自身。下面是一些接口声明的例子：

```Deeplang
interface Eq {
    fun equals(this, other : This) : Bool;
}
```

```Deeplang
type Order [ Eq, Lt, Gt ]

interface Ordered extends Eq {
    fun compare(this, other : This) : Order;
}

interface Add {
    fun add(this, other : This) : This;
}
interface Mul {
    fun mul(this, other : This) : This;
}
```

假设`I`是一个接口，那么`I`也可以被用作类型，此时它表示任意实现了接口`I`的类型。当需要表达“同时实现了若干个接口的类型”时，可以利用一个没有方法的空接口以及接口的依赖列表来实现，例如：

```Deeplang
// 接口Number等价与接口Ordered + Add + Mul
interface Number extends Ordered, Add, Mul {
}
```

```Deeplang
fun some_function(a : Number, b : Number) : Number {
    if (equals(a, b))
        return add(a, a);
    else
        return mul(a, a);
}
```

## 接口实现

在Deeplang中，为一个类型`T`实现接口`I`的语法如下：

```Deeplang
impl I for T {
    fun <方法名字>(<参数列表>) -> <返回值类型> {
        <方法的实现>
    }
}
```

在方法的实现中，可以用`this`来访问方法的调用者。除了实现接口外，也可以直接为一个类型实现一些方法，语法为：

```Deeplang
impl T {
    ... // 同上
}
```

在这种`impl`块中实现的方法将能够被类型为`T`的值调用。下面是一个通过接口来模拟鸭子类型的例子：

```Deeplang
interface Quack {
    quack() -> ();
}

```Deeplang
    type Duck [ RubberDuck ]
    impl Quack for Duck {
        fun quack() -> () {
            print("quaaaack");
        }
    }
    
    type Bird [ Snidget ]
    impl Quack for Bird {
        fun quack() -> () {
            print("bird quaaaack");
        }
    }
    
    fun sound(animal: Quack) -> () {
        animal.quack();
    }
    
    fun main() -> () {
        let duck: Duck = Duck();
        let bird: Bird = Bird();
    
        // type checking pass
        sound(duck); // quaaaak
        sound(bird); // bird quaaaak
    }
```

## 命名规范总结

以下名字必须以小写字母开头：

- 变量、函数的名字
- 结构体的域的名字

以下名字必须以大写字母开头：

- 类型、接口的名字
- 代数数据类型的分支的名字

除此之外，名字中可以包含下划线、字母和数字（首字母不能为数字）。上述“首字母”指的都是第一个非下划线的字母，也就是说不管是哪一种名字，都允许以若干个下划线开始，但只有下划线的名字是不被允许的。上述命名规范是语法的一部分，而不是一种软性的建议。违反上述命名规范的程序是语法错误的。但除了首字母外，Deeplang的使用者可以自由选择名字其他部分的命名规范，例如选择驼峰命名法或下划线命名法。

## 仍在设计中的特性

Deeplang目前正处于活跃开发中。上述的设计和特性都尚未稳定，随时可能被更改。下面是一些仍在讨论中的特性，它们可能会在未来成为语言的一部分。

### 数组宏

Deeplang是一门面向IoT的语言，在IoT编程中一个十分重要的应用场景就是对各类二进制协议的高效解析。关于Deeplang中如何支持这一场景仍在讨论中。其中一个语言层面的方案是支持内建的数组操作宏，例如：

```dp
let arr: [i32; 100] = [];
arr@match([s] == 1, [s + 10] == 1);
```
