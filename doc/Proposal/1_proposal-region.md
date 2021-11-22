# Proposal for Region Based Memory Management
This document aims to be a comprehensive description
on how the memory management system is deduced,
from the weakness of traditionally region-based memory management systems.
Examples in this document would use a C-like syntax and semantic,
with the following definitions:
```c
struct List {
    int value;
    List *next;
};
```

## Complexity of Memory Management
Before introducing regions,
let's focus on the problem of automatic memory management first.
We first show the complexity of this problem by an example:
```c
List *push_n(int n, List *l) {
    if (n == 0)
        return l;
        
    List *new_cell = (List *)malloc(sizeof(List));
    new_cell->value = n;
    new_cell->next = l;
    return push_n(n - 1, new_cell);
}
```
The function `push_n` has the following characteristics:
1. it may create *unbounded* number of new references (proportional to `n`)
2. all the newly created references are returned
2. cells in the returned list don't have uniform lifetime.
They are a mixture of those newly created and those already in `l`.

These characteristics result in potentially troublesome usage of `push_n`:
```c
void trouble1(int n, List *l) {
    if (n == 0)
        return;
        
    List *l2 = push_n(n, l);
    printf("%d\n", l2->value); // l2 can not be optimized away in general
    trouble1(n - 1, l);
}
```
Upon reaching the recursive call to `trouble`,
those newly created elements in `l2` are no longer needed,
while those in `l` are still needed as an argument to `trouble1`.
It is impossible at compile time,
by inspecting `l2`,
to know which elements to reclaim,
as there may be arbitarily many elements created by `push_n`.
But if `l2` is kept as-is and is not reclaimed,
`n` unused references will be left on the heap every iteration,
resulting in a memory leak proportional to `n` squared!

While very advanced whole-program analysis may be able
to generate proper deallocation code by inspecting at the source of `push_n`,
such analysis is typically expensive in terms of compilation time,
and usually has difficulty scaling to a more complete language with more features.

## Regions to the Rescue
An approach to solve the above problem is using *regions*.
A region is used to allocate and hold references.
At runtime, the runtime system is able to find all the references
in a region, and reclaim them altogether.
By using the concept of region,
we can properly deallocate the above function.
From now on, assume we have the following functions pre-defined:
```c
typedef ... Region;

// create a new region
Region new_region();
// allocate a reference in [region] of size [size]
void *ralloc(Region region, size_t size);
// reclaim all references in [region]
void rfree(Region region);
```
Now a region'ed version of `push_n` and `trouble1` is as follows:
```c
List *push_n_region(Region r, int n, List *l) {
    if (n == 0)
        return l;
        
    List *new_cell = (List *)ralloc(r, sizeof(List));
    new_cell->value = n;
    new_cell->next = l;
    return push_n_region(r, n - 1, new_cell);
}

void trouble1_solved(Region r, int n, List *l) {
    if (n == 0)
        return;
        
    Region local_region = new_region();
    List *l2 = push_n_region(local_region, n, l);
    printf("%d\n", l2->value);
    rfree(local_region);
    return trouble1_solved(r, n, l);
}
```
Now let's inspect the source carefully to see how region operates.
The function `push_n_region` has signature
```c
List *push_n_region(Region r, int n, List *l);
```
It now accepts an extra region argument `r`.
This argument is provided by the caller of `push_n_region`,
and is used to allocate those references that
*need to be returned to the caller*.
In the definition of `push_n_region`, we now use, instead of `malloc`,
`ralloc` to allocate the new cell:
```c
List *new_cell = (List *)ralloc(r, sizeof(List));
```
As `new_cell` will be returned to the caller of `push_n_region`.

Now let's inspect the caller of `push_n_region`, `trouble1_solved` here.
`trouble1_solved` still receives an extra region argument `r` for
returning values,
however since it returns nothing, this is just for consistency.
The real interesting part is its definition.
`trouble1_solved` creates a new region `local_region`:
```c
Region local_region = new_region();
```
As the name indicates,
this region is used to allocate those values local to
this particular call to `trouble1_solved`.
Now the call to `push_n` becomes:
```c
List *l2 = push_n_region(local_region, n, l);
```
As `l2` is *not* returned to the caller of `trouble1_solved`.
Notice that `l` is not allocated in `local_region`,
so now we can easily tell those new references and those from `l` apart!
After the `printf` statement,
`local_region` reaches its eno of life,
and its memory is reclaimed via:
```c
rfree(local_region);
```
Those references created by `push_n_region` will be reclaimed here,
while those in `l` will not!
So region successfully conquer the memory management of `trouble1`,
*completely automatically* (region codes in this example can be automatically inferred),
safely, and without any memory leak!

Now let's establish a little on our current region system,
for clarity of later discussions:
1. every function now accepts an extra region argument,
used to allocate references that need to be returned to the caller.
2. whether a references would be returned to the caller
is determined by inspecting whether it occurs in the returned expression,
directly or indirectly.
3. if a reference is not returned to the caller,
it is allocated in a local region, created per function call.
The local region is freed before the function returns to the caller.

## Trouble of Regions, Part I
So far the region approach seems promising,
however, more careful inspection reveals its weakness.
Specifically,
if we look at the code of `push_n_region`,
the new cell is considered part of return value,
just because it occurs in the returned expression,
another recursive call to `push_n_region`.
However, what if `push_n_region`'s return value does not contain its parameter?
To see what would happen, let's construct another example hehe:
```c
List *bad(Region r, List *acc, List *l) {
    if (l == NULL)
        return rand() % 2 == 0 ? NULL : acc;
        
    List *new_acc = ralloc(r, sizeof(List));
    new_acc->value = l->value;
    new_acc->next = acc;
    return bad(r, new_acc, l->next);
}
```
This function is basically the list reversal function,
except that it sometimes returns the null list at random.
Since `acc` (and hence the `new_acc` allocated in `bad`)
may still be returned,
they have to be allocated in the region `r` for return values.
However, this can lead to severe memory leak:
```c
int trouble2(Region r, int n, List *l) {
    if (n == 0)
        return l;
        
    int l2 = bad(r, NULL, l);
    printf("Automatic memory management is IMPOSSIBLE, just give up!\n");
    return trouble2(r, n - 1, l2 == NULL ? l : l2);
}
```
Here `l2` is used in the recursive call to `trouble2` and will
eventually get returned.
So the region argument passed to `bad` should be `r`.
However, whenever `bad` returns `NULL`,
the intermediate list cells created in `bad` will leak,
producing memory leak proportional to `<length of l> * n`.

## Per-Region GC
The `bad` example above illustrate that it is impossible to
identify which region some reference should belong to precisely at compile time,
and conservative approximation may cause linear or worse memory leak.
So how can we solve this problem then?
If something cannot be determined at compile time,
then the only choice is to react to it at runtime!
But how?
For runtime memory management,
the most famous technique is undoubtedly Garbage Collection.
But (tracing) GC is not very *modular*:
the requirement for a root set containing all live variables
means we can't perform GC on only a portion of the heap to reduce the overhead.

Luckily, regions again provide useful properties this time.
For simplicity, let's first consider an immutable setting.
In an immutable setting, observe that:

> within its lexical scope,
a reference can never be referenced by something outside its lexical scope.

with this property in hand, if we are to collect
*only variables in a region*,
we only need to consider the variables *within the same lexical scope*.
That is, the current activation record is sufficient as the GC root for the region.
Now, we can perform a partial GC on only the record, at a low cost!
Recall that the trouble we are facing is that,
it is impossible to determine which references would escape to the caller
and which would not at compile time.
To solve this problem, we simply allocate these references into a local region,
and perform a local GC!
Before reclaiming the local region,
a simple local liveness analysis can give us a set of roots:
the values that are within the same lexical scope
(and hence possible to point to values in the region).
Then we simply perform a usual copying GC,
with the *FROM* space being the local region,
and the *TO* space being the region for return values.
Here's a simple version of peseudo code for the GC routine:
```cpp
void collect_region(vector<Pointer> roots, Region from, Region to) {
    vector<Pointer> new_roots;
    for (Pointer &ptr : roots) {
        for (Value &field : *ptr) {
            if (is_pointer(field) && is_in_region((Pointer)field, from)) {
                void *new_pos;
                if (already_moved(*field)) {
                    new_pos = *field;
                }
                else {
                    new_pos = ralloc(to, sizeof(*ptr));
                    memcpy(new_pos, ptr, sizeof(*ptr));
                    new_roots.push_back((Pointer)field);
                }
                field = new_pos;
            }
        }
    }
    
    if (! new_roots.is_empty())
        collect_region(new_roots, from, to);
    else
        rfree(from);
}
```
Now let's see how per-region GC can solve the previous problem:
```c
int trouble2_solved(Region r, int n, List *l) {
    if (n == 0)
        return l;
        
    Region local_region = new_region ();
    int l2 = bad(local_region, NULL, l);
    /* [l] is not part of the root set, because it is not created
     * in the same lexical scope as [local_region] */
    collect_region({ l2 }, local_region, r);
    return trouble2(r, n - 1, l2 == NULL ? l : l2);
}
```
Here `bad` is assigned a local region.
Before the recursive call to `trouble2`,
GC is performed on `local_region`, with `l2` being the root set.
So any references in `local_region` accessible from `l2`
will be copied to `r`, as desired.
While other references in `local_region` will be destroyed with `local_region`
after the GC.

At first sight the need to copy the whole list when `l2` is not `NULL`
may seem expensive.
But this is necessary, as more complex examples can easily be constructed.
Consider the following expression:
```c
List *drop_n(int n, List *l) {
    if (l == NULL || n == 0)
        return l;

    return drop_n(n - 1, l->next);
}

List *bad2(Region r, List *acc, List *l) {
    if (l == 0)
        return drop_n(rand() % 20, acc);

    List *new_acc = ralloc(r, sizeof(List));
    new_acc->value = l->value;
    new_acc->next  = acc;
    return bad2(r, new_acc, l->next);
```
Here what references will be returned by `bad2`
is simply undecidable at compile time.
So GC, either global or per-region, is necessary.

### Possible Optimizations
Although the per-region GC should eliminate troublesome memory leaks,
it is still quite inefficient, despite the potentially small size of data it operates on.
The `is_in_region` predicate also adds to its complexity,
if regions are of unbounded size.
Given that the per-region GC routine is triggered much more often than usual global GC,
it is necessary to perform some optimizations to reduce the cost of the per-region GC.
So here are some possible optimizations for per-region GC:
1. only those references that may or may not be returned require GC,
so we can perform a 3vl (three valued logic) analysis on functions to find out whether
they return their parameters.
And only perform per-region GC for those references that may or may not get returned.
2. the above analysis can be made more precise,
by extending plain variable liveness to something structural.
For example, distinguishing between references held in a list
and reference to the list itself may reduce the amount of values to GC.
3. since per-region GC only happens at some pre-defined points,
the type, and hence structure, of all concerned values can be known in advance,
this information can be used to generate site-specific GC routine so as to perform completely tagless GC.
4. references allocated in a region that requires per-region GC
may be tagged with the region they should be copied to when performing the GC.
This can be beneficial when combined with the region splitting approach
introduced below, to avoid references from being copied multiple times.
5. per-region GC may be postponed, so long as the system still has enough memory.
In this case, the runtime should maintain a list of regions that requires GC,
the set of roots should also be tracked.
It is unknown whether postponing per-region may result in any performance gain,
though.

To slightly relieve concerns about the cost of per-region GC,
notice that in many programs the lifetime of variables are clear,
in these cases, the first optimization above can completely eliminate
the need for per-region GC.
Also, given that traditional global GC scans the whole heap,
per-region GC should be much faster unless the region under concern
ends up eating up most of the heap.

### Mutability
The above analysis are all performed in an immutable setting.
For a mutable setting,
the assumption that values would only get referenced by other values within the same lexical scope
no longer holds.
So we need to extend the root set now.
A simple analysis should be adequate to determine which outside references may be mutated
to point to some newly allocated references.

However, mutability will cause another severe issue.
Consider the following example:
```c
List *trouble_mut(Region r, List **l_ref, List *l) {
    List *l2 = ralloc(???, sizeof(List));
    l2->value = 1;
    l2->next  = l;
    *l_ref = l2;
    return l2;
}
```
What should be filled in `???`?
The problem is, we don't know which of `r` and the region of `l_ref`
will live longer, if looking only at `trouble_mut`.
Fortunately, we can make use of the runtime to resolve this problem.
We require the runtime to be capable with:
1. get the region of a mutable reference.
The simplest way would be to tag every mutable reference with its region.
Other methods, such as by inspecting the address, are OK, too.
2. compare two regions.
Here we cannot compare the lifetime of `r` and that of the region of `l_ref`,
because both are parameter to `trouble_mut`.
However, at runtime, only concrete regions exist,
and hence it should be easy to compare two regions' lifetime.

With these two capabilities,
we simply calculate the region with longer lifetime at such conflicts,
and then substitute `???` with it.

## Trouble of Regions, Part II
Even after introducing some form of partial GC,
unfortunately, our current region system may still have severe memory leak problem.
Consider the following example:
```c
void trouble3(Region r, int n) {
    if (n == 0)
        return;

    Region local_region = new_region();
    List *l = push_n_region(local_region, n, NULL);
    printf("%d\n", l->value);
    trouble3(r, n - 1);
    printf("It's still not overrrrr!!!\n");
    rfree(local_region);
    return;
}
```
Here `l` is not returned, and safely deallocated
with `local_region` before returning.
The problem is, the recursive call to `trouble3`
is not in tail position,
and is before the returning of the outer call.
So `l` will live *after* the recursive call to `trouble3`,
resulting in a memory leak proportional to `n * n`.
However, if we can reclaim `l` *before* the recursive call to `trouble3`,
the space cost would be only proportional to `n`,
due to nested call stacks of non-tail recursion.
Luckily, this problem can be solved easily, with more local region:
```c
void trouble3_solved(Region r, int n) {
    if (n == 0)
        return;

    Region local_region1 = new_region();
    Region local_region2 = new_region();

    List *l = push_n_region(local_region2, n, NULL);
    printf("%d\n", l->value);
    rfree(local_region2);

    trouble3_solved(r, n - 1);
    printf("Is this the end?\n");
    rfree(local_region1);
    return;
}
```
Here we introduce two local regions.
One lives until the `trouble3_solved` returns,
and one lives until the recursive call to `trouble3_solved`.
Since the lifetime of `l` ends before the recursive call,
it is allocated in `local_region2`,
and is reclaimed before the recursive call,
eliminating the aforementioned memory leak.

The last issue left is, when to split local regions?
Obviously, assigning a new region for every statement is unacceptably expensive.
So some critical statements must be classified,
and local regions should split at these critical statements.
These critical statements should be those that are *expensive*,
i.e. those that may take up a lot of time and space.
More specifically, we classify the following statements as critical:
- recursive call to self in the definition of a recursive function
- entering the next iteration of a loop statement

The following statements may optionally be considered critical, too:
- call to recursive function (not self)
- before entering a complete loop statement
- potentially expensive operating system utilities

The region system creates one local region for each critical statement
at the beginning of function,
and free the region right before its corresponding statement.

## Trouble of Region, Part III
So far we have mostly dealt with recursive functions and data types,
and the "unboundedness" they bring.
However, one more complexity of memory management arise from multiple
references to the same value and control flow branching.
For example, given the following definition:
```c
struct ListPair {
    List *fst;
    List *snd;
};

ListPair mk_pair(Region r, int n, List *l) {
    return { push_n_region(r, n, l), push_n_region(r, n, l) };
}
```
It is impossible to determine which of `fst` and `snd`, or both,
are needed by the caller in `mk_pair`,
so it must allocate both in `r`.
Now, if a caller only make use of one of the two lists,
since both are allocated in the same region,
it seems that the other won't get reclaimed and will cause a leak.
Consider the following example:
```c
List *trouble4(Region r, int n, List *l) {
    if (n == 0)
        return l;
        
    ListPair pair = mk_pair(r, n, l);
    List *l2 = rand() % 2 == 0 ? pair.fst : pair.snd;
    return trouble4(r, n - 1, l2);
}
```
Since some part of `pair` is needed as the return value anyway,
`pair` is allocated in `r`,
which, when `l2` is `fst`, cause `snd` to leak.
Fortunately, solution to this problem is easy.
Observe that although some part of `pair` is needed anyway,
all the fields in `pair` are not *always* needed.
So this suggest that for the whole `pair` itself,
the situation should be "may or may not be returned",
instead of "always returned".
With this new strategy in mind, we can solve `trouble4` easily:
```c
List *trouble4_solved(Region r, int n = 0, List *l) {
    if (n == 0)
        return l;
        
    Region local_region = new_region();
    ListPair pair = mk_pair(local_region, n, l);
    List *l2 = rand() % 2 == 0 ? pair.fst : pair.snd;
    // recall that this is the per-region GC function
    collect_region({ l2 }, local_region, r);
    return trouble4(r, n - 1, l2);
}
```
No matter `l2` is actually `fst` or `snd`,
the other will correctly be reclaimed by `collect_region`.

## Final Design
In its most simple setting, the region system should work as follows:
1. programs (perhaps in ANF) are split into different segments
at *expensive operations*, i.e. before recursive call or entering next loop.
2. for each of these program segment, a local region is created.
Every function is augmented with an extra region argument.
3. a local lifetime analysis of references is performed at each segment,
references are allocated in the last region that they *must* live.
4. at the end of each region, a per-region copying GC is performed
5. (optimization of (4))
the lifetime analysis in (3) is extended to a
3vl analysis. If no reference in a region *may* live after the region dies,
the region is simply freed without performing the GC.
6. (possible optimization)
regions don't play well with tail calls.
Region freeing or region GC code must be inserted after the tail call.
To restore tail call optimization,
functions may receive some extra region arguments
and be responsible to free or GC them.
The function may reuse these regions directly as well.

### Possible Implementation Hints
- Regions may be implemented as a list of pages
- By bounding the size of each stack frame,
we can use the stack directly for small regions.
When the size of the region plus stack variable size exceeds
the maximum size, a pointer to the next region page is inserted
at the end of the stack.
