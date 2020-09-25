#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int coleman_liau_index(string text)
{
  int length = strlen(text);
  int letters = 0;
  int words = 0;
  int sentences = 0;

  for (int i = 0; i < length; i++)
  {
    char token = text[i];

    if (isalpha(token))
    {
      letters += 1;
    }
    else if (isspace(token))
    {
      words += 1;
    }
    else if (token == '?' || token == '!' || token == '.')
    {
      sentences += 1;
    }
  }

  float L = ((float)letters / ((float)words + 1)) * 100;
  float S = ((float)sentences / ((float)words + 1)) * 100;
  return round(0.0588 * L - 0.296 * S - 15.8);
}

int main(void)
{

  string text = get_string("Text:");
  int grade = coleman_liau_index(text);

  if (grade < 1)
  {
    printf("Before Grade 1\n");
  }
  else if (grade > 16)
  {
    printf("Grade 16+\n");
  }
  else
  {
    printf("Grade %i\n", grade);
  }
}