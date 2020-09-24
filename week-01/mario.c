#include <stdio.h>
#include <cs50.h>

int get_number_between(int start, int finish, string label);
void repeat_character(char character, int repeats);

int main(void)
{
  char brick = '#';
  int gap = 2;

  int height = get_number_between(1, 8, "Height:");

  for (int i = 0; i < height; ++i)
  {

    repeat_character(' ', height - 1 - i);
    repeat_character(brick, i + 1);
    repeat_character(' ', gap);
    repeat_character(brick, i + 1);
    putchar('\n');
  }
}

void repeat_character(char character, int repeats)
{
  for (int i = 0; i < repeats; ++i)
    putchar(character);
}

int get_number_between(int start, int finish, string label)
{
  int number;

  do
  {
    number = get_int("Height: ");
  } while (number < 1 || number > 8);

  return number;
}