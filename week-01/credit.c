#include <stdio.h>
#include <cs50.h>

int get_number_length(long number);
int get_first_digit(long number);
int get_first_two_digits(long number);
void print_card_type(long number);
bool checksum(long number);

int main(void)
{

  long card_number = get_long("Number:");

  if (checksum(card_number))
  {
    print_card_type(card_number);
  }
  else
  {
    printf("INVALID\n");
  }
}

int get_number_length(long number)
{
  int length = 0;

  while (number != 0)
  {
    number /= 10;
    ++length;
  }

  return length;
}

int get_first_digit(long number)
{
  while (number >= 10)
  {
    number = number / 10;
  }

  return number;
}

int get_first_two_digits(long number)
{
  while (number >= 100)
  {
    number = number / 10;
  }

  return number;
}

bool checksum(long number)
{
  int sum = 0;
  int count_from_end = 0;

  while (number != 0)
  {
    int digit = number % 10;

    if (count_from_end % 2 == 0)
    {
      sum += (digit);
    }
    else
    {
      int multiply = digit * 2;

      if (multiply < 10)
      {
        sum += multiply;
      }
      else
      {
        sum += (multiply % 10) + ((multiply / 10) % 10);
      }
    }

    number /= 10;
    ++count_from_end;
  }

  return sum % 10 == 0;
}

void print_card_type(long number)
{
  int first = get_first_digit(number);
  int first_two = get_first_two_digits(number);
  long length = get_number_length(number);

  if ((first_two >= 51 && first_two <= 55) && length == 16)
  {
    printf("MASTERCARD\n");
  }
  else if ((first_two == 34 || first_two == 37) && length == 15)
  {
    printf("AMEX\n");
  }
  else if (first == 4 && (length == 16 || length == 13))
  {
    printf("VISA\n");
  }
  else
  {
    printf("INVALID\n");
  }
}