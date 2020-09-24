# Intoduction to C

## Overview

```c
// main part of program
int main(void)
{

}
```

```c
// printf = print format
prinf("hello %s\n", answer);
// %s - placeholder
// \n - new line
// answer - variable
```

```c
// import helper functions
#include <stdio.h>
```

source code -> compiler -> machine code

## Functions

```
return_type function_name( parameter list ) {
   body of the function
}
```

example:

```c
int max(int num1, int num2) {

   int result;

   if (num1 > num2)
      result = num1;
   else
      result = num2;

   return result;
}
```

write function at top to 'hoist'

```c
int max(int num1, int num2)
```

known as a prototype

## Another example

```c
//Promp user for positive integer
int get_positive_int(void)
{
  int n
  do
  {
    n = get_int("Positive Integer:");
  }
  while (n < 1);
  return n
}
```

## Overflow

Computers have limitations with numbers based on number of bits available
for example if only 3 bits are available
111 (7 in decimal) in binary if we plus 1 we get 000 as there is no way to
represent 8 (known as overflow) y2k had this issue
