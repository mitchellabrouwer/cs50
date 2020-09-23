# Data types

## Basic types - specify type of variable at creation

- int - integer, always (4 bytes). -2^31 to 2^31-1 (~-2 billion to ~2 billion)
- char - single characters (1 byte)
- float - has a decimal (real numbers) (4 bytes). Be careful with precision
- double - decimal (8 bytes) - double precision
- void - no return type / placeholder for 'nothing'
- bool - true or false
- string - series of characters
- _Bool and String not built into C use #include <cs50.h> for course_
- _note: 1 byte has 8 bits_

## Qualifiers - add precision to data type

- signed - may be positive and negative
- unsigned - the number is always positive. For example an unsigned int's range is 0 to ~4 billion
- const - can't change
- short / Long - reduces or increases the range
- volitile - may be changed by processes outside the current program

## Customising types:

- struct (Structures) - encapsulate numerious pieces of data in one variable
- typedef - create custom types based on existing type. Eg could shorten variable name

## Declaration example:

```c
int number; // declaration
int height, width // declaration

number = 17  // assignment
```

Only declare variables when you need them. Not just at the beginning of the program
Only specify type when declaring

# Operators

- arithmetic operators - +, -, /, _, %, +=, -=, /=, _=, ++, --
- boolean expressions - AND (&&), OR (||) NOT (!), >, >=, <, <=, ==, !=

# Coditionals (branches)

- if...then
- if...then...else
- if...then...else if...else if...else
- if...if...if...else - else will only bind to nearest if
- switch statement - optional breaks for each case
- ternary operator - int x = (expr) ? 5 : 6

# Loops

- while(true)... - infinite loop
- while(bool) - unknown number of loops
- do...while - at least once, unknown number of loops
- for loop (int i = 0; i < 10; i++ ) - discrete number of times (start, expression, increment)
