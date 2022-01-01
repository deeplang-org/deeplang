# 新内存管理机制设计

`C++` 的内存管理机制比较依赖原始指针，智能指针虽然可以作为辅助，但智能指针仍然可以很容易获取原始指针，这非常容易产生内存问题，但使用上很方便。

而 `rust` 的内存管理机制借助生命周期和所有权管理，相比前者提升了很多安全性，但使用上很困难。

这个设计的目标是为了在这两者之间寻求一个平衡点，希望探讨一种比 `c++` 更安全，但比 `rust` 使用上简便的新机制，以给系统编程语言的内存管理提供新的方案。

因为不追求如同 `rust` 一样的内存安全保证，因此该机制在部分场景会舍弃掉一些安全性。

## 值

数字类型、布尔类型是典型的值类型，这些类型的实例都是不可变的，每经过一次传递都会复制值本身。这些类型一般只存在于栈上，不需要特殊的内存管理手段支持。

```
func f(a: Int, b: Int) -> Int {
    return a + b
}
let x = 1
let y = 2
let z = f(x, y)
```

同理，如果一个结构体中的成员都是值类型，那么这个结构体的实例依然符合上面的规则，无论这些成员是否拥有内部可变性。

```
struct Point {
    let x: Int
    let mut y: Int
}

func f(a: Point, b: Point) -> Point {
    let mut c = Point{a.x+b.x, a.y+b.y}
    c.y = c.y + 1
    return c
}
let x = Point{1,1}
let y = Point{2,2}
let z = f(x, y)
```

## 指针

指针分为两类：

- 裸指针，与 c++ 指针的语义一致，但限制它只能在 unsafe 上下文中使用。
- 智能指针，对现代 c++ 提供的几种智能指针内嵌语法支持，可以满足一些简单的场景。

### raw

即裸指针，需要开发者手动申请和释放，编译器不保证其安全性。但通过限制其可以被使用的位置，尽量减少风险覆盖范围。

裸指针只能在 unsafe 标注的块、函数、类型中使用。

```
struct Point {
    let mut x: Int
    let mut y: Int
}

unsafe func f(a: raw Point, b: raw Point) -> raw Point {
    let mut c: raw Point = new Point{a.x+b.x, a.y+b.y}
    c.y = c.y + 1
    return c
}

unsafe {
    let x = new Point{1,1}
    let y = new Point{2,2}
    let z = f(x, y)
    delete x
    delete y
    delete z
}
```

在 unsafe 中可以提供解引用和取地址操作，这里应该覆盖 c 所有的操作，由程序员自己控制安全性。

### unique

unique 指针用来描述唯一所有权的指针类型，这种类型只能从一个位置移动到另一个位置，移动过后原位置就不能再使用。

unique 指针提供非常低的门槛安全地使用指针，并且可以由编译器计算回收时间，不增加运行时开销。

```
let a: unique Foo = unique Point{1, 2};
let b: unique Foo = a; // 从 a 移动 到 b
print(a.x); // 编译报错，a 已经被转移
```

当作用域结束后当前还持有的 unique 指针将会自动释放。

```
func f(a: unique Point, b: unique Point) -> unique Point {
    let mut c: unique Point = unique Point{a.x+b.x, a.y+b.y}
    c.y = c.y + 1
    return c
    // 释放 a 和 b
}

let x = unique Point{1,1}
let y = unique Point{2,2}
f(x, x) // 报错，x 不能被连续转移
let z = f(x, y) // 转移 x 和 y
// 释放 z
```

### shared

shared 指针用来描述采用引用计数的指针类型，这种类型的所有权是共享的，可以将一个指针分配给多个所有者。

shared 指针提供了一种简单的方式使用可以被共享的指针，可以使用的范围比 unique 更大，但需要程序员自己解决循环引用的问题。

shared 指针不是简单的指针结构，它需要包含计数需要的额外成员，并且编译器只能计算引用增加和减少，真正的回收必须通过运行时，显然这会增加运行时开销，无论是内存还是计算。

```
let a: shared Foo = shared Foo(1, 2);
let b: shared Foo = a; // b 是 a 的别名
b.x = 2
print(a.x); // 仍然可以使用 a
```

当所有引用都结束了作用域之后，即引用计数为 0，当前还持有的 shared 指针将会自动释放。

```
func f(a: shared Point, b: shared Point) -> shared Point {
    let mut c: shared Point = shared Point{a.x+b.x, a.y+b.y}
    c.y = c.y + 1
    return c // c 引用计数不变
    // a 和 b 引用 - 1
}

let x = unique Point{1,1}
let y = unique Point{2,2}
f(x, x) // ok，x 引用 + 2
let z = f(x, y) // x 和 y 引用 + 1
// z 引用计数 - 1
// x y 引用计数 - 1
// x y z 引用计数都是 0，释放
```

## weak

weak 指针是结合 shared 使用的特殊指针，和 shared 一样它的所有权也是共享的，可以分配给多个所有者，但它不会影响引用计数。

weak 指针必须与可空标记一起使用，weak 有可能为空。

暂未设计具体细节。

## 引用

引用是一种特殊的机制，它实际上仍然是指针，但引用通过一些限制，可以让指针的使用变得更安全。过于复杂的引用机制会让语言变得复杂，因此我们可以借鉴 c# 的经验，只在某些地方提供引用，尽可能只在常用的地方引入引用，而不把它设计为一种类型。

引用可以通过受限的上下文来使用，使用引用代替值或指针可以减少对实例拷贝开销，实现更高的性能。

引用通过 ref 声明，ref 不是类型的一部分，只能用在局部变量定义、函数形参、函数返回类型。

ref 作用的类型必须是值类型，不能是指针类型。但在使用处，指针类型可以同样使用 ref 语法传入参数使用，这样可以基本达到重载使用的目的。

```
func f1(ref a: Point) {
    a.x = 2;
}

func f2(ref a: unique Point) { // 报错， ref a 不能是指针类型
}

func f3(ref a: shared Point) { // 报错， ref a 不能是指针类型
}

func g() {
    let x = Point{1, 1};
    let ref xr: Point = ref x; // ok，允许获取局部引用
    f1(ref x); // ok，传入值类型

    ley y = unique Point{1, 1};
    f1(ref y); // ok，传入指针类型

    let z = shared Point{1, 1};
    f1(ref z); // ok，传入指针类型
}
```

ref 返回类型不能接受局部的引用，这样就保证了不会发生逃逸行为。

```
func f1(ref a: Point) -> ref Point {
    return a // 合法，可以将接受的引用返回出去
}

func f2() -> ref Point {
    let b = Point{1, 1}
    let ref a = ref b
    return a // 不合法，不能将局部引用返回
}
```

这和 rust 的生命周期非常相似，但我们不在类型上引入这个机制，只在实现层面隐含了类似的检查，以避免引入巨大的复杂度。

