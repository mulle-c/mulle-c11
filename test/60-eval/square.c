/* THIS TEST WAS WRITTEN BY PHIND. It missed initially
  1. SQUARE needs a dummy identifier parameter
  2. MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR needs to be wrapped in MULLE_C_EVAL
  3. <mulle-c11/mulle-c11-eval.h> needs to be included.
  But it came up, with the wrapper idea which is nice. Unfortunately it messed
  up the wrapper, but anyway...
*/

/*
The MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR macro is a convenient utility provided by the Mulle C11 library. It is designed to apply a given macro to a list of arguments, separating the results with commas. This can be useful when working with variadic arguments or other situations where you need to perform an operation on multiple items and separate the results with a comma.

Here's a breakdown of how the MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR macro works:

1. It takes three arguments: a macro, a list of arguments, and a final argument. The macro is applied to each element in the list, and the results are separated by commas.

2. The macro uses a series of other helper macros to handle the iteration and comma separation. These include MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR_1, MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR_2, MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR_3, and so on. Each of these helper macros takes care of applying the given macro to one or more elements in the list and separating the results with commas.

3. The MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR macro is implemented using variadic macro arguments, which allows it to accept a variable number of arguments for the list. This makes it highly flexible and adaptable to various use cases.

Here's an example of how you might use the MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR macro:
*/

#include <stdio.h>
#include <mulle-c11/mulle-c11.h>
#include <mulle-c11/mulle-c11-eval.h>

#define SQUARE(x) ((x) * (x))
#define WRAPPED_SQUARE(x, _) SQUARE(x)

int main() {
  int result[] = { MULLE_C_EVAL( MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR(WRAPPED_SQUARE, 1, 2, 3, 4) ) };

  for (size_t i = 0; i < sizeof(result) / sizeof(result[0]); ++i) {
    printf("result[%zu] = %d\n", i, result[i]);
  }

  return 0;
}


/*
In this example, the MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR macro is used to apply the SQUARE macro to a list of numbers (1, 2, 3, 4). The results are separated by commas and stored in an array. When compiled and executed, the output will be:

```
result[0] = 1
result[1] = 4
result[2] = 9
result[3] = 16
```

As you can see, the MULLE_C_FOR_EACH_WITH_COMMA_SEPARATOR macro provides a convenient way to perform operations on multiple items and separate the results with commas, making it a useful tool in the Mulle C11 library.
*/