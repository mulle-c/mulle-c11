# Datatypes

The datatypes in C can be classified like this:

- **Scalar**:
  - Single primitive type (e.g., `int`, `float`).
  - Register based or Stack-allocated, fixed size.
  - No destructor needed
  - Simple copy (bitwise OK).
  - Passed by value.
  - Simplest data type, no management overhead.

- **Simple Struct (e.g., `CGPoint`)**:
  - Holds only primitive types (e.g., `float x, y`).
  - Stack-allocated, no heap memory.
  - No destructor needed; auto-cleaned when out of scope.
  - Simple copy (bitwise OK).
  - Usually passed by value.
  - In use, almost as easy as a scalar, closer to scalar than a Smart Struct.

- **Complex Struct**:
  - Holds pointers to heap-allocated data (e.g., `char *name`).
  - Stack- or heap-allocated; manages dynamic resources.
  - Requires destructor to `free` pointers/resources.
  - May need deep coping to avoid pointer issues.
  - Usually passed by pointer.
  - Complex, like a mini-object with resource management.

- **C-Array**:
  - Fixed-size sequence (e.g., `int arr[10]`) or dynamic (e.g., `int *arr = malloc(...)`).
  - Stack/static for fixed arrays; heap for dynamic.
  - No destructor for stack arrays; `free` needed for heap arrays.
  - Memory copy for stack arrays (via `memcpy`); deep copy for heap arrays.
  - Always passed by pointer (decays to pointer in functions).


## Creation of a **Scalar**

"Creation" of a scalar from another scalar or conversion between scalars is
done with `_to_` or `To`.

Example:

``` c
static float   deg_to_rad( float deg);
```

Otherwise use the 'C' operator `=` (duh) and constants:

```c
uintptr_t    index = mulle_not_found;
```


## Creation of a **Simple Struct**

A simple struct is constructed with `_make` or `Make` or as assignment of
a constant struct:

``` c
struct mulle_range    range = mulle_range_make( 1, 2);
struct CGPoint        point = CGPointZero;
```


## Creation of a **Complex Struct**

For the "complex" struct there is a whole chapter devoted to
[SYNTAX](SYNTAX.md). You use init/done for stack based variables:

``` c
struct my_complex_type   data;

my_complex_type_init( &data, NULL);
my_complex_type_done( &data);
```


or create/destroy for heap based ones:

``` c
struct my_complex_type   *p;

p = my_complex_type_create( NULL);
my_complex_type_destroy( p);
```


## Creation of a **C-Array**

none. mulle-c data structures may operate on arrays internally, but the array
as a data structure is not adorned with any functions.

