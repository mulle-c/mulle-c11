# mulle-c11 Library Documentation for AI
<!-- Keywords: c11, macros, preprocessor, attributes, endian, constructors, utilities -->

## 1. Introduction & Purpose

`mulle-c11` is a foundational cross-platform compatibility layer that abstracts C11 language features and compiler-specific extensions behind consistent, portable preprocessor macros. Its primary purpose is to enable the use of modern C language features—like type alignment, function attributes (constructor/destructor), compiler builtins (branch prediction, bit counting), and preprocessor metaprogramming—across diverse compilers (GCC, Clang, MSVC) and platforms (Linux, macOS, Windows, Cosmopolitan).

It solves the portability problem by providing a unified API for compiler-specific capabilities with graceful degradation: supported features expand to native compiler syntax; unsupported features expand to safe no-ops. This eliminates the need for scattered `#ifdef` blocks in dependent code and is a dependency for virtually all other `mulle-sde` C and Objective-C projects.

## 2. Key Concepts & Design Philosophy

**Compiler Glue Layer**: The library exists entirely through header files and preprocessor macros with zero runtime overhead. Each macro abstracts a compiler feature, testing for compiler capability at compile time.

**Graceful Degradation**: The core philosophy ensures maximum portability. When a compiler supports a feature (e.g., `__attribute__((constructor))`), the macro expands to native syntax. If unsupported, it degrades to a safe alternative, allowing compilation without errors. Code remains functional even if specific optimizations or features are unavailable.

**Platform Abstraction**: Handles platform-specific differences:
- **Compiler Features**: GCC/Clang attributes vs MSVC `__declspec`
- **Symbols**: Export/import declarations for DLL vs static linking
- **Integer Types**: Platform-dependent sizes and endianness
- **Boolean Types**: C99 vs custom implementations

**Zero Configuration**: Works out-of-the-box; optional configuration via preprocessor defines allows fine-tuning behavior for specific build scenarios (e.g., compiling Windows DLLs with static library constituents).

## 3. Core API & Data Structures

The library's API is entirely macro-based; it defines no data structures or runtime functions. All functionality is compile-time or compile-time-configurable.

### 3.1. Function Attributes & Compiler Hints (`mulle-c11.h`)

#### Inlining Control
- `MULLE_C_ALWAYS_INLINE`: Forces function inlining (GCC/Clang: `__attribute__((always_inline))`; MSVC: `__forceinline`)
- `MULLE_C_NEVER_INLINE`: Prevents inlining (GCC/Clang: `__attribute__((noinline))`; MSVC: `__declspec(noinline)`)
- `MULLE_C_STATIC_ALWAYS_INLINE`: Combines `static` with `MULLE_C_ALWAYS_INLINE` for optimal cross-platform performance

#### Return Value Optimization
- `MULLE_C_CONST_RETURN`: Marks function as `const`—return value depends only on parameters, no side effects (enables aggressive compiler optimizations)
- `MULLE_C_NONNULL_RETURN`: Indicates function's return value is never NULL (enables null-check elimination)
- `MULLE_C_CONST_NONNULL_RETURN`: Combines both `const` and `nonnull return` attributes

#### Parameter Safety
- `MULLE_C_NONNULL_FIRST`: First parameter must not be NULL
- `MULLE_C_NONNULL_SECOND`: Second parameter must not be NULL
- `MULLE_C_NONNULL_FIRST_SECOND`: First two parameters must not be NULL
- `MULLE_C_NONNULL(idx)`: Parameter at index `idx` must not be NULL
- Compiler emits warnings if called with NULL; enables null-check elimination

#### Deprecation & Special Semantics
- `MULLE_C_DEPRECATED`: Marks function as deprecated; compiler emits warning on use
- `MULLE_C_NO_RETURN`: Specifies function never returns (e.g., `abort()`, `exit()`); enables dead-code elimination
- `MULLE_C_UNUSED`: Marks parameter or variable as intentionally unused; suppresses compiler warnings

#### Visibility & Linkage
- `MULLE_C_EXTERN_GLOBAL`: For DLL scenarios; controls global variable linkage (default: `extern`)
- `MULLE_C_GLOBAL`: Global variable declaration with visibility control (platform-specific: `__declspec((dllexport))` on Windows)

### 3.2. Automatic Function Execution

#### Constructor & Destructor Functions
- `MULLE_C_CONSTRUCTOR(name)`: Declares function that runs automatically when library/program loads
  - **Use Cases**: Initialize global state, register callbacks, load resources
  - **Scope**: Before `main()` or equivalent entry point
  - **Platform Mapping**: GCC/Clang `__attribute__((constructor))`; MSVC `#pragma init_seg` or CRT initialization
  
- `MULLE_C_DESTRUCTOR(name)`: Declares function that runs automatically when library/program unloads
  - **Use Cases**: Cleanup global state, deallocate resources
  - **Scope**: After `main()` exits or on `dlclose()` for shared libraries
  - **Platform Mapping**: GCC/Clang `__attribute__((destructor))`; MSVC `atexit()` wrapper

#### Performance Note
Constructors/destructors have guaranteed execution but order is not guaranteed between different compilation units. Design with that constraint in mind.

### 3.3. Compiler Builtins & Performance Hints

#### Branch Prediction
- `MULLE_C_LIKELY(expr)`: Hints that expression is likely true; compiler optimizes for true branch
  - Typical use: `if( MULLE_C_LIKELY(ptr != NULL) )`
  - Performance impact: Can improve instruction cache efficiency
  
- `MULLE_C_UNLIKELY(expr)`: Hints that expression is likely false; compiler optimizes for false branch
  - Typical use: `if( MULLE_C_UNLIKELY(error_condition) )`

#### Bit Manipulation
- `mulle_c_popcount(x)`: Counts set bits in `unsigned int` (native: `__builtin_popcount()`)
- `mulle_c_popcountl(x)`: Counts set bits in `unsigned long`
- `mulle_c_popcountll(x)`: Counts set bits in `unsigned long long`
- **Fallback**: Portable C implementation if builtin unavailable
- **Use Case**: Bitmap operations, Hamming distance, set cardinality

#### Expect Builtin (Clang/GCC)
- `__builtin_expect(expr, value)`: Advanced branch prediction; rarely used directly (use `MULLE_C_LIKELY`/`MULLE_C_UNLIKELY` instead)

### 3.4. Type Alignment

#### C11 Standard Support
- `alignas(type)`: Align variable to boundary of `type` (e.g., `alignas(16) int buffer[256]`)
- `alignof(type)`: Get alignment requirement of `type` (e.g., `alignof(double)`)
- **Platform Handling**: Uses `<stdalign.h>` when available; falls back to compiler builtins

#### Compatibility
- Gracefully handles platforms without C11 (Windows, older compilers)
- Configurable via `MULLE_C11_NO_STDALIGN` (set by library for non-supporting platforms)

### 3.5. Endianness Detection (`mulle-c11-endian.h`)

Preprocessor defines for compile-time endianness checks:
- `__LITTLE_ENDIAN__`: Defined on little-endian platforms (x86, x86-64, ARM)
- `__BIG_ENDIAN__`: Defined on big-endian platforms (PowerPC, SPARC)
- **Use Case**: Network byte order conversions, binary data layout optimization

### 3.6. Optional Type Extensions

#### Integer Types (`mulle-c11-integer.h`)
- `NSINTEGER_DEFINED`: Defines `NSInteger`, `NSUInteger` for cross-platform compatibility
- **Purpose**: Bridges C and Objective-C integer type universes

#### Boolean Type (`mulle-c11-bool.h`)
- Provides `MULLE_BOOL_DEFINED` and bool-related macros
- **Purpose**: Consistent boolean handling across C99 and non-C99 environments

### 3.7. Preprocessor Metaprogramming (`mulle-c11-eval.h`)

Advanced compile-time evaluation for macro-based generic programming:
- Argument counting: Determine number of variadic arguments at compile time
- Conditional expansion: `#if` alternatives based on compile-time conditions
- Repetition: Code generation via macro recursion
- Token manipulation: Stringify, concatenate, transform identifiers
- **Use Cases**: Type-safe macro families, compile-time data structure instantiation

**Key Macros**:
- `MULLE_C_STRINGIFY(x)`: Convert identifier to string literal
- `MULLE_C_CONCAT(a, b)`: Concatenate two identifiers
- `MULLE_C_ASSERT(condition)`: Compile-time assertion; build fails if false

## 4. Performance Characteristics

- **Runtime Overhead**: Zero. All macros expand at compile time; no dynamic execution.
- **Memory Footprint**: Zero. Header-only library with no compiled code.
- **Compile Time**: Negligible increase from header parsing and macro expansion.
- **Binary Size**: No impact; purely compile-time.
- **Optimization Coverage**: Enables compiler optimizations (inlining, null-check elimination, branch prediction); potential runtime speed improvements.

## 5. AI Usage Recommendations & Patterns

### Best Practices

1. **Always use `mulle-c11` macros instead of raw compiler-specific syntax**:
   - ✅ `MULLE_C_ALWAYS_INLINE` (portable across GCC, Clang, MSVC)
   - ❌ `__attribute__((always_inline))` (GCC/Clang-only, fails on MSVC)

2. **Use `MULLE_C_ALWAYS_STATIC_INLINE` for static helpers**:
   - Handles cross-platform inline semantics automatically
   - Preferred over manual `static inline` for consistency

3. **Leverage parameter safety macros in public API functions**:
   - `MULLE_C_NONNULL_FIRST` catches NULL-pointer mistakes early
   - Enables compiler null-check elimination

4. **Constructors for one-time global initialization**:
   - Ideal for registering callbacks, initializing thread-local storage, allocating shared resources
   - Keep self-contained; don't depend on other constructors' ordering

5. **Branch prediction for hot paths**:
   - Use `MULLE_C_LIKELY` on success paths in error handling
   - Measurable improvement on tight loops; negligible elsewhere

### Common Pitfalls

1. **`MULLE_C_ASSERT` scope limitation**:
   - ❌ At global scope: `MULLE_C_ASSERT(1);` (fails)
   - ✅ Inside function body: `void foo() { MULLE_C_ASSERT(sizeof(int) == 4); }`

2. **Constructor/destructor dependencies**:
   - Don't assume constructor execution order between translation units
   - Design as if constructors run in parallel (though they don't)

3. **Overusing branch hints**:
   - Branch prediction has minimal impact on modern CPUs
   - Significant benefit only in tight, predictable loops
   - Don't use speculatively; profile first

4. **Forgetting platform-specific behavior**:
   - `MULLE_C_CONSTRUCTOR` is thread-safe; test on target platforms (Linux, macOS, Windows, Cosmopolitan)
   - `MULLE_C_GLOBAL` controls symbol visibility across different platforms

### Idiomatic mulle-sde Usage Patterns

**Pattern 1: Safe Public API with Null Checks**
```c
MULLE_C_NONNULL_FIRST
MULLE_C_NONNULL_SECOND
MULLE_C_CONST
struct mulle_container *mulle_container_get_element( struct mulle_container *c, void *key )
{
    // Compiler knows c and key are non-null; enables optimizations
    ...
}
```

**Pattern 2: Hot-Path Loop Optimization**
```c
void process_items( struct mulle_array *items )
{
    for( size_t i = 0; i < mulle_array_get_count(items); i++ )
    {
        void *item = mulle_array_get_element_at_index(items, i);
        if( MULLE_C_LIKELY(item != NULL) )
            handle_item(item);  // Optimized branch
        else
            handle_error();     // Rare branch
    }
}
```

**Pattern 3: One-Time Library Initialization**
```c
MULLE_C_CONSTRUCTOR(init_mylib)
static void init_mylib(void)
{
    // Initialize global state, register callbacks, etc.
    g_initialized = 1;
}
```

## 6. Integration Examples

### Example 1: Cross-Platform Function Attributes

This demonstrates using various attributes to guide compiler optimization.

*Source: `test/30-inline/` and `README.md`*

```c
#include <mulle-c11/mulle-c11.h>
#include <stdio.h>

// Guarantees fast inlining and compiler optimization hints
MULLE_C_STATIC_ALWAYS_INLINE
MULLE_C_CONST_RETURN
MULLE_C_NONNULL_FIRST
int string_length_hint(const char *s)
{
    // Compiler can:
    // 1. Inline this at call site
    // 2. Assume s is never NULL (eliminates null checks)
    // 3. Apply const-folding if s is compile-time known
    
    int len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

// Branch prediction for error handling
int safe_process_string(const char *input)
{
    if (MULLE_C_UNLIKELY(input == NULL)) {
        fprintf(stderr, "Error: null input\n");
        return -1;
    }
    
    int len = string_length_hint(input);
    if (MULLE_C_LIKELY(len > 0)) {
        printf("Length: %d\n", len);
        return len;
    }
    
    return 0;
}

int main(void)
{
    int result = safe_process_string("Hello");
    return result < 0 ? 1 : 0;
}
```

### Example 2: Automatic Initialization & Cleanup with Constructors

Demonstrates library initialization and teardown.

*Source: `test/10-constructor/` and `test/20-destructor/`*

```c
#include <mulle-c11/mulle-c11.h>
#include <stdio.h>
#include <stdlib.h>

// Global resource
static int *g_resource_pool = NULL;

// Runs automatically before main()
MULLE_C_CONSTRUCTOR(init_resources)
static void init_resources(void)
{
    printf("[Constructor] Initializing resource pool...\n");
    g_resource_pool = malloc(1024);
    if (!g_resource_pool) {
        fprintf(stderr, "Failed to allocate resource pool\n");
        exit(1);
    }
}

// Runs automatically after main() exits
MULLE_C_DESTRUCTOR(cleanup_resources)
static void cleanup_resources(void)
{
    printf("[Destructor] Cleaning up resource pool...\n");
    if (g_resource_pool) {
        free(g_resource_pool);
        g_resource_pool = NULL;
    }
}

int main(void)
{
    printf("Main: Resource pool ready at %p\n", g_resource_pool);
    return 0;
}

// Output:
// [Constructor] Initializing resource pool...
// Main: Resource pool ready at 0x...
// [Destructor] Cleaning up resource pool...
```

### Example 3: Compile-Time Assertions & Type Checks

Using preprocessor metaprogramming to enforce constraints.

*Source: `test/50-assert/` and `mulle-c11-eval.h`*

```c
#include <mulle-c11/mulle-c11.h>
#include <stdio.h>
#include <stddef.h>

// Ensure this code only compiles on 64-bit systems
MULLE_C_ALWAYS_STATIC_INLINE
void function_for_64bit_only(void)
{
    MULLE_C_ASSERT(sizeof(void *) >= 8);
    printf("Running on 64-bit system\n");
}

// Memory layout validation
typedef struct {
    char  a;      // 1 byte
    int   b;      // 4 bytes (may have padding)
    long  c;      // 8 bytes
} packed_struct;

// Compile-time size verification
void validate_struct_size(void)
{
    MULLE_C_ASSERT(sizeof(packed_struct) <= 16);
    printf("Struct size validated: %zu bytes\n", sizeof(packed_struct));
}

int main(void)
{
    function_for_64bit_only();
    validate_struct_size();
    return 0;
}
```

### Example 4: Bit Counting with Compiler Builtins

Demonstrates cross-platform bit manipulation.

*Source: `README.md` examples*

```c
#include <mulle-c11/mulle-c11.h>
#include <stdio.h>

// Count set bits in bitmask (used for feature detection, Hamming distance, etc.)
unsigned int count_features(unsigned int feature_mask)
{
    // Uses __builtin_popcount() on GCC/Clang, portable C fallback otherwise
    return mulle_c_popcount(feature_mask);
}

// Example: Determine how many CPUs are available (bitmask)
int main(void)
{
    unsigned int cpu_mask = 0x0F0F0F0F;  // 16 CPUs available
    unsigned int cpu_count = mulle_c_popcount(cpu_mask);
    
    printf("Available CPUs: %u\n", cpu_count);
    printf("CPU mask: 0x%08X\n", cpu_mask);
    
    // Output: Available CPUs: 16
    return 0;
}
```

### Example 5: Platform-Aware Endianness Handling

Using compile-time endianness detection.

*Source: `mulle-c11-endian.h` and network code*

```c
#include <mulle-c11/mulle-c11.h>
#include <stdint.h>
#include <stdio.h>

// Network byte order is big-endian; detect platform endianness at compile time
uint32_t host_to_network(uint32_t host_value)
{
#ifdef __LITTLE_ENDIAN__
    // Little-endian host: swap bytes
    return ((host_value & 0xFF000000) >> 24) |
           ((host_value & 0x00FF0000) >> 8)  |
           ((host_value & 0x0000FF00) << 8)  |
           ((host_value & 0x000000FF) << 24);
#elif defined(__BIG_ENDIAN__)
    // Big-endian host: no swap needed
    return host_value;
#else
    #error "Cannot determine endianness"
#endif
}

int main(void)
{
    uint32_t host_value = 0x12345678;
    uint32_t network_value = host_to_network(host_value);
    
    printf("Host:    0x%08X\n", host_value);
    printf("Network: 0x%08X\n", network_value);
    
    return 0;
}
```

## 7. Dependencies

`mulle-c11` has **no external dependencies**. It is a foundational library at the base of the `mulle-sde` dependency graph. All other `mulle-sde` projects depend on it for portability infrastructure.
