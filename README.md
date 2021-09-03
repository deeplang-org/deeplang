<a href = "https://github.com/deeplang-org/deeplang">
<img width="40%" src="./assets/banner.jpg" alt="Deeplang" /></a>

Deeplang语言是一个学生科研性质的编程语言，由来自浙大、中科大、帝国理工等学校的同学共同完成。这是一种静态类型、强类型语言，按照C-style设计语法，同时支持面向对象、过程式和逻辑式的混合范式。我们致力于将Deeplang语言打造为一个具有鲜明内存安全特性的面向IoT场景的语言。安全特性参考Rust、Cyclone、Verona等语言的安全机制。为了在资源受限的IoT场景下运行该语言，我们选择了更合适的解释执行的模式。

Deeplang的独特安全特性帮助其具有一定的竞争力。作者正在持续的开发和迭代中。

协同项目:

- [Deeplang Type System](https://github.com/deeplang-org/deeplang-type-system) : Deeplang Frontend based on [OCaml](https://ocaml.org/)
- [DeepVM](https://github.com/deeplang-org/deepvm) : Deeplang Backend based on [wasm](https://webassembly.org/)

---
# 目录
1. [注释](#注释)
1. [程序入口](#程序入口)
1. [控制语句](#控制语句)
1. [变量定义](#变量定义)
1. [函数](#函数)
1. [基础类型](#基础类型)
1. [高级类型](#高级类型)
1. [表达式](#表达式)


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
在Deeplang程序中，顶层代码没有表达式，只有各类定义。

比如类，函数，变量等：
``` dp
class Foo {};

fun bar() -> () {};

let a: i32 = 1;
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
循环控制语句，与流行语言不通，Deeplang中的for语句初始化需要用花括号包裹

所定义的变量生命周期在退出for循环后结束
``` dp
for ({let i: Int = 0}; i < 10, i++) {
    foo();
};
```

# 变量定义
以let定义的变量是常量，let mut定义的变量是可变的。
``` dp
let foo: i32 = 1;
let mut bar: i32 = 1;

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

# 基础类型

## 基本类型

``` dp
    bool
    tuple                
    ()                   // empty tuple alias Unit type
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



# 高级类型

## 代数数据类型

使用 `type` 构造新的类型，后跟值构造器的数组。

`this` 表示自身的值，`This` 则表示自身的类型。

```
type Shape [
	Rectangle(width: i32, height: i32),
	Circle(radius: i32)
];

```

## match 控制流

代数数据类型可以绑定方法。

可以用 `match` 语句访问数据域。

```
type Shape [
	Rectangle(width: i32, height: i32),
	Circle(radius: i32)
] {
	fun area(this: This) -> i32 {
		let ret: i32;
		match(this) {
			Rectangle(width, height) {
				ret = width * height;
			}
			Circle(radius) {
				ret = PI * radius * radius;
			}
		}
		return ret;
	}
};
```



## 结构体

和 C++ 等的 class 不同，是 ADT 中 Product Type 的语法糖。

```
type Rectangle(width: i32, height: i32) {
	fun area(this: This) -> i32 {
        return this.width * this.height;
    }
};

//desugar
type Rectangle [
	Rectangle(width: i32, height: i32)
] {
	fun area(this: This) -> i32 {
        return this.width * this.height;
    }
};
```

## Interface

参考了 rust 中的 `trait` 和 haskell 中的 `typeclass`，类似于 typescript 里的 `interface`，但只能定义方法。

用 `type` 关键字进行定义。

```
type Show {
    show: This -> string
};
```

类型定义中，使用 `impl` 关键字来派生 `trait` 。

```
type Person (age: i32, name: string) impl Show {
    fun show(this: This) -> string {
        return "Hello Deeplang";
    }
};

```

## 实例化

可以使用值构造子来实例化一个 type , 并且可以使用 point 操作符来访问实例中的方法和属性。

拥有默认的构造函数。

``` dp
let foo: Rectangle = Rectangle(10, 10);

foo.area(); // 100
```

## 鸭子类型

通过 `interface` 来实现鸭子类型。

```
type Quack {
    quack: () -> ();
}

type Duck() impl Quack {
    fun quack() -> () {
        print("quaaaack");
    }
}

type Bird() impl Quack {
    fun quack() -> () {
        print("bird quaaaack");
    }
}

fun sound(animal: Quack) -> () {
    animal.quack();
}

let duck: Duck = Duck();
let bird: Bird = Bird();

// type checking pass
sound(duck); // quaaaak
sound(bird); // bird quaaaak
```

## 委托

将一个类型的数据域委托到当前层级。

```
type Animal (weight: i32);
type Person (
    age: i32,
    name: string,
    as animal: Animal // delegate
);
let p: Person = Person(60, 30, 30);
p.weight;
```



# 表达式

## 常量表达式
目前Deeplang中有两种常量表达式
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
目前Deeplang不支持自定义宏，并只提供builtin的数组方法宏，可以用来简化数组操作

宏调用以 @ 操作符开始，后跟调用的宏名
``` dp
let arr: [i32; 100] = [];
arr@match([s] == 1, [s + 10] == 1);
```





