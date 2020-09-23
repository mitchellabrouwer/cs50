#include <stdio.h>
#include <cs50.h>

int main(void)
{
  string name = get_string("What is your name?\n");
  printf("hello, %s\n", name);
}

// compile: make hello (clang -o hello hello.c o = output flag)
// run: ./hello
// if yeilding errors try help50 make hello
