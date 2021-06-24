# Go 泛型设计

## 背景

一门静态类型语言从2009年诞生，经过很多年的发展，还是保持没有泛型，硬是靠着本身的素质在工业语言里挖出一块蛋糕，这在2021年看来本身就是一件不可思议的事情。

最近这个语言终于要下决心要考虑泛型了，这意味着其中必然存在非常慎重的设计考量，可能值得我们去了解一下。

毕竟一个能拖延十年不加泛型的语言，最终加上泛型的故事我们一辈子可能也不会经历几次。

## 基础概念

了解这个语言的泛型之前，需要先理解部分基础设计，才能更好体会后面的设计取舍。

这里先假定大家对 c++ 和 java 的泛型有最基础的了解。

### 结构体

go 中用结构体定义自定义数据结构，这部分跟 c++ 差不多，除了语法有些差异。

```go
type Foo struct {
    x int
    y int
}
```

### 成员方法

go 的类型跟 c++ 和 java 的 class 一样可以定义成员方法。

唯一的差异是语法不在类型定义里面，而是在外面用了特殊的函数写法。

这是一个普通的函数，参数是 Foo。

```go
func f(a Foo) {}

func main() {
    var a = Foo{}
    f(a)
}
```

这是一个Foo的成员函数。

```go
func (a Foo)f() {}

func main() {
    var a = Foo{}
    a.f()
}
```

### 接口

go 的接口是一种静态鸭子类型，只要一个类型包含接口描述的所有成员方法，这个类型的实例被认为实现了接口，并可以被传递给该接口。

这不需要实现类型显式声明实现接口，实现类型只需要满足接口要求即可传递，这也被称为隐式接口。

```go
type I interface {
    f()
}

func main() {
    var a = Foo{}
    var i I = a
}
```

那么一个不包含任何要求的接口，实际上可以包含任意类型，即自动拥有了一个 top type。

```go
type Any interface {}

func main() {
    var a = Foo{}
    var i Any = a
}
```

### 通过代理实现接口（模拟继承）

go 里没有 class，没有 c++ 和 java 那样的显式继承机制。

对于需要复用场景，go 提供了一种类似代理的机制，可以部分模拟继承。

任何类型内的代理成员，它的实例可以像继承一样直接访问代理成员的成员。

但这仍然不是继承，新类型和代理成员没有子类型关系。

```go
type Base struct {
    v int
}

func (Base)f() {}

type Sub struct {
    Base // 声明一个代理类型
    // 解糖为含有一个 Base Base
}

func main() {
    var a = Base{}
    a.v = 2
    var b = Sub{}
    b.v = 2 // ok
    b.Base.v = 2 // ok
    
    b = a // error
    b.f() // ok
}
```

这种代理同样可以访问成员方法，所以就能用来实现接口，在抽象能力上近似于继承。

```go
type Base struct {}
func (this Base) f() {}

type Sub1 struct {
    Base
}

type Sub2 struct {
    Base
}
func (this Sub2) f() {}

type I interface {
    f()
}

func main() {
    var i I = Sub1{}
    i.f() // 调用 Base 的版本
    i = Sub2{}
    i.f() // 调用 Sub2 的版本
}
```

### 正交的类型语法

go 的类型语法其实是一种特殊的语法，它使用 type 作为最前面的关键字是有含义的，这种语法实际上是将类型别名和具名类型的语法融合在了一起。

类型名称后面的部分实际上是类型表达式，在一个可以使用类型的地方，基本都可以直接使用类型表达式代替。

例如 go 其实没有官方提供的 Any 接口。空接口就自动代表了 Any。

```go
func f(any interface{}) interface{} {
    return any
}

type I interface {}

func main() {
    var any interface{} = 0
    var b I = f(any)
}
```

## 泛型

go 在没有泛型之前，主要用这几个特性代替泛型的功能。

- go 的接口非常容易用来抽象，如果业务需求已经能描述具体的成员方法，那直接用接口就可以了
- go 有一套非常容易使用的运行时反射，如果能接受运行时开销的代价，反射可以运行时访问成员，类型上可以 Any 一把梭
- go 提供了内置的代码生成器，对于需要提供通用复合类型的场景，可以用这种方式生成类型代码，跟宏类似
- 对于使用最频繁的几种泛型类型（List、Map、Channel），go 已经提供了对应的内置泛型类型，只是没开放泛型功能给开发者

靠着以上几个功能的支撑，go 虽然没有泛型，但是也在云计算、数据库、区块链等领域玩的风生水起。

很显然的，没有泛型依然可以通过其它手段做到抽象的功能，只是都有一定的代价。

为了更干净地实现功能抽象，大部分语言最终都还是引入了泛型相关的概念，go 也一样。

### 泛型语法

go 的泛型语法没有选用常见的 `<>`，而是使用了 `[]`。

```go
type A[T Any] struct {
    v T
}

func g[T Any](v T) {}
```

对于不使用 `<>` 的理由是 go 团队不想处理下面这种歧义。

```
a, b = w < x, y > (z)
```

对于不使用 `()` 的理由也是因为不想处理歧义。

```
interface { M(T) }
```

但这仍然会存在歧义，go 的下标语法也是 `[]`，但是 go 团队愿意处理这个歧义。

```
f[a](b) // 区分不出是下标还是泛型，只能靠语义
```

实际上歧义最少的做法是把下标语法改成 `()`，把下标认为是函数调用操作符重载，然后泛型就可以用完全无歧义的 `[]` 了（scala 的做法）。

### 泛型约束

go 的泛型参数和函数参数一样一定要带一个类型，这个类型就是泛型约束。

go 的接口天然是用来描述约束的，所以 go 的泛型直接就使用接口来表示约束，约束的类型只能是接口类型。

```go
type A[T interface{}] struct { // 可以传入任何 T
    v1 T
    v2 T
}

type I interface {
    f()
}

type B[T I] struct { // 只能传入含有 f() 的类型
    v1 T
    v2 T
}
```

go 的代理机制，在这个地方也有妙用。

对于值类型，如果想实现一个通用的包装类，保证传递后的可变性，通常可以定义一个 `Box<T>` 来实现。

但是这种实现的缺点是无法直接访问该类型的成员。

```swift
class Box<T> {
    var value: T
    init(v: T)
}

struct A {
    var v: Int
    init(i: Int)
}

func main() {
    var box = Box<A>(A(1))
    box.value.v = 2
}
```

但 go 可以让这个事情变得更简单

```go
type Box[T Any] struct {
    *T
}

type A struct {
    v int
}

func main() {
    var box = Box[A]{ &A{} }
    box.v = 2
}
```

这意味着 Box 还能自动实现 T 实现的所有接口，这对于设计特定的代理类型会非常方便。

### 类型列表

由于 go 现在还没设计扩展机制，即使有了上面的能力，也很难对基础类型进行抽象，比如设计一个对所有 int 类型都适用的函数，就做不到了。

为此 go 给接口引入了类型列表的特性，通过在接口内指定能实现的类型，就可以算出有限的集合，这个集合共有的能力就是这个接口能使用的能力。

```go
type Integer interface {
    type int8, int16, int32, int64
}

func add[T Integer](a T, b T) T {
    return a + b
}
```

这就是实际意义上的 union type。

通过这个特性，实现 Nullable 类型和 Option 类型就成为了轻而易举的事情。

```go
type Nullable[T Any] interface {
    type Nil, T
}

type Nil struct {}

var nil = Nil{}

func f1() {
    var x Nullable[int] = 0
    x = nil
}

type Option[T Any] interface {
    type None, Some[T]
}

type None struct {}

type Some[T Any] struct {
    T
}

func f2() {
    var x Option[int] = None
    x = Some[int]{ 0 }
}

type IT[T1 Any, T2 Any, T3 Any] interface {}
```

或者是经典的 List 类型

```go
type List[T Any] interface {
    type Nil, Cons[T]
}

type Cons[T Any] struct {
    head T
    tail List[T]
}
```

