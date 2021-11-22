# Proposal for a Borrow Checker and a Lifetime System

## Introduction
The goal of this proposal is to describe a design of a
lifetime-borrow system.
The system would provide important extra usability to
a ownership based system,
while preserving memory safety.

The core principles of the system is similar to that of Rust.
That is, it is designed around the following principles:
- Every object has a unique owner throughout its lifetime
- *Either* one mutable borrow *or* many immutable borrows may coexist.
- *No* borrows can exist when assigning to the owner

The system is a combination of two parts:
- An explicit language, where annotations are needed everywhere,
used to check correctness
- An inference algorithm, which tries to insert proper annotations
to unannotated programs

## The Explicit Language
- A *lifetime* is an abstract identifier
used to indicates how long some objects may live
- Every object is attached to a lifetime.
This lifetime is explicitly annotated
- An object must not live longer than its lifetime
- There can be some constraints over lifetimes.
We are concerned with the following:
    * `a <= b`, indicating `b` should live longer than `a`
    * `a <=! b`, similar to `a <= b`,
    but also requiring that `a` is the only reference such that `a <= b`
    * `unique b`, indicaing there is no lifetime `a` such that `a <= b`
- These constraints are flow-sensitive, i.e. different set of constraints
may be present at different program points
- Lifetimes are created implicitly at their first occurence.
However, lifetimes are explicitly destroyed via a `free l` statement,
where `l` is a lifetime.
- Constraints must be satisfied at every program point.
For example, if `a <= b`, then `a` must be destroyed
when `b` is destroyed
- If an immutable borrow of a reference has lifetime `a`,
while the borrowed object has lifetime `b`,
the constraint `a <= b` must be satisfied.
- If an mutable borrow of a reference has lifetime `b`,
while the borrowed object has lifetime `b`,
the constraint `a <=! b` must be satisfied
(before `a` is destroyed)
- When an owned object is assigned,
the constraint `unique b` must be satisfied at this program point.

The explicit language should also contain rules for unique ownership.
But they are not the topic of this proposal, hence omitted.

## The Inference Algorithm
Requiring annotations on all objects,
and requiring explicitly destroying lifetimes is very cumbersome.
So an inference algorithm that automatically inserts such annotaions is highly necessary.

The inference algorithm works as follows:
- At every object creation, a fresh lifetime variable is created
- Borrows of every object is tracked along the data flow
- On creation of mutable borrow and assignment to owned object,
a `free` statement is inserted,
destroying the lifetime of all existing borrows of that object,
and all their sub-lifetimes

## Function Signature
A primary burden of lifetime system is the need to
annotate functions with proper lifetime.
There are several options here:
- try best to infer all lifetime annotations.
A full inference algorithm may be possible,
but is probably not principal, due to polymorphic recursion.
Also minor change in function implementation may affect
the inferred signature, resulting in mysterious errors
- requiring annotations on every function definition
- allow inference, as well as explicit annotation.
And consider explicit lifetime annotations on exported
functions as a good practice.

## Typed Lifetime and Path Lifetime
(This extension seems appealing, but is not yet designed in depth)
Another verbosity of Rust's borrow checker is that
it requires annotations on every struct declaration.
Although an elision rule is possible,
it needs to dive arbitarily deep into struct fields,
and may create too many lifetime variables for structs
with many fields.
To tackle this issue,
we propose *typed* lifetimes and *path* lifetimes.

Typed lifetimes, as its name indicates,
are lifetimes with a type attached.
All objects with such a lifetime must has the same type.
With typed lifetime as a basis,
we can now introduce *path* lifetime.
Given that `S` is a struct type, `f` is a field of `S`,
then for some lifetime `a : S`,
`a.f@b` is also a lifetime, where `b` is a lifetime name.
This lifetime has the same type as `f`.

Path lifetimes provide a mechanism to avoid making
the possibly many lifetime variables explicit.
Furthermore, it can support *non-uniform* lifetime of structs.
That is, different instances of structs may have different lifetime patterns.
This can be especially useful for recursive data structures.

So how does path lifetimes work, then?
A path lifetime is much like an ordinary lifetime,
except that it is attached to a field of an object.
Hence the rules above for borrows, assignments, etc. also applies.
Some extra constraints need to be introduced:
- If an object has lifetime `a`, then `a.f@b <= a` for any field `f` of the object
That is, if the whole object is assigned or destroyed,
all its fields must also be assigned or destroyed.
- If the object actually in field `f` has lifetime `c`, then `a.f@b <= c`,
and `c <= a.f@b` (i.e. the two should be equivalent)
(TODO: should we use a smarter way to avoid contradiction with mutable borrows?)

These constraints, especially the first one,
can also be hard-coded into the type checking system directly,
avoiding some unnecessary constraints.

Some modifications to the inference algorithm is also necessary:
- On assigning a field, the old lifetime of the field, say `a.f@b`,
is destroyed. Another fresh path lifetime, say `a.f@c` is created,
and the above constraints are created again for `a.f@c`.

### Remark
One can view path lifetimes as a compact way to mimic structural types.
Consider a type system with only structural structs
(i.e. all fields and their types are explicitly stored in the type of the whole struct).
In this case, no lifetime annotation is needed,
as all lifetime information are also explicitly stored in the type of the struct.
Furthermore, non-uniform lifetime also comes for free.

But structural struct types are typically very lengthy and verbose.
As every field and its type will appear in the struct's type.
Now that we are only concerned about lifetimes,
we introduce *path lifetimes* as an alternative way to represent the lifetime information
of individual fields explicitly.
Now struct types can be written compactly as usual,
but full lifetime information can also be specified explicitly via path lifetimes.
As a bonus, only those path lifetimes that we are concerned with will appear in the function signature,
making function signatures more compact.

### Variant Types and Recursive Types
Extending path lifetimes to variant types (tagged unions) is highly desirable.
As they are heavily used in recursive data types.
The extension is similar to that for struct types.
Take the type `t option` (where `t` is another type) as an example,
if `a` is a lifetime of type `t option`,
then `a.some` is an lifetime of type `t`.

When it comes to recursive data types,
obviously there will be infinitely many path lifetimes.
To make inference decidable, some sort of approximation is necessary.
Consider the following example
(the example uses rust-like syntax,
but with a simplified semantic.
It should be self-explainig):
```rust
enum List<A> {
    Nil,
    Cons(A, List<A>)
}

fn nth<A>(n : int, l : &List<A>) -> &A {
    match l {
        Nil => { abort!(); }
        Cons(hd, tl) => {
            if (n == 0) {
                &hd
            } else {
                nth(n - 1, &tl)
            }
        }
    }
}
```
What should be the signature of `nth`?
In fact `nth`'s most precise signature is:
```rust
fn nth<A>(n : int, l : &'a List<A>) -> &'b A
    where 'b <= 'a.Cons.1.Cons.1. ... .Cons.0
```
But the number of `.Cons.1` in the middle is undecidable at compile time.
So an opproximation should be a lower bound of
all the possible paths.
Here `'a` is a suitable choice.

## Spine Lifetime
The above system is not compatible with higher kinded polymorphism
(polymorphism over type constructors).
If this feature is to be supported,
some higher-kinded form of lifetime is necessary.
A possible (but not yet verified) solution is:
for polymorphic type constructors,
we make the restriction that *all their type arguments have uniform lifetimes*.
For example, for a unary type constructor (e.g. `List`),
we assume that all occurences of `A` in `List<A>` have uniform lifetime.
Under this restriction, we can introduce a new form of lifetime,
called spine lifetime, of the form `a.#i`,
where `a` is a lifetime, and `i` is an integer indicaing the position
of type argument.
This lifetime represents the lifetime of the `i`-th type argument
of the (polymorphic) type constructor.

This approach quite imprecise,
due to the assumption that all occurences of the same type argument
have uniform lifetime.
For the case where a type argument occurs in both covariant
and contravariant positions,
it becomes extremely unintuitive.
So this is just a heuristic approach.
After all,
having fine control over memory behavior
requires knowledge about underlying structure of data,
which contradicts the concept of higher kinded polymorphism.
