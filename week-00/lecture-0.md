# Lecture 0 - Computational Thinking, Scratch

## Basics of how computers work

- Binary - base 2 vs decimal base 10
- Bit - 0 or 1
- Byte - 8 bits
- Transistor - switch between 0 and 1 states, used to represent and store values in a computer chip (think of as a bit)
- Everything is represented by a number e.g. A = 65 (ASCII)
- Unicode(can be 32 bits) is a superset of ASCII(8 bits)
- Pixels - represented by RGB eg RGB(72, 73, 33) = yellow
- Video - a series of images flying past your eye so quickly we perceive as
  actual movement
- all information reduces to 0's and 1's
- algorithms - just step by step instructions for solving some problem. e.g. how to find for a name in a phone book
- input => algorithms => outputs

## Simple algorithm example - phone book problem in pseudocode:

```
1.  Pick up phone book
2.  Open to middle of phone book
3.  Look at page
4.  If Smith is on page
5.    Call Mike
6.  Else if Smith is earlier in the book
7.    Open to middle of left half of book
8.    Go bak to line 3
9.  Else if Smith is later in the book
10.   Open to middle of right half of book
11.   Go back to line 3
12. Else
13.   Quit
```

## Basics of programming

- Funcitons - what to do
- Conditions - branches / forks in the road
- Boolean expressions - questions that have yes or no (1 or 0)
- Loops - repeat something over and over
- Variables
- Threads - thread of execution, threads are a way for a program to split itself
  into two or more simultaneously
- Events - like a secret message passed from one program to another

_DRY - easier to maintain. change in one place instead of multiple_

_Abstraction - hides complexity, dont have to care how or why something is implemented, smaller and much less prone to errors_
