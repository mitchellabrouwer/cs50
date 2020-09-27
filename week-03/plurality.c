#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

const int MAX = 9;

typedef struct
{
  string name;
  int votes;
} candidate;

candidate candidates[MAX];

void print_winner(void)
{
  int maximum = candidates[0].votes;

  for (int i = 1; i < MAX; i++)
  {
    if (candidates[i].votes > maximum)
    {
      maximum = candidates[i].votes;
    }
  }

  printf("%i\n", maximum);

  for (int i = 0; i < MAX; i++)
  {
    if (candidates[i].votes == maximum)
    {
      printf("%s\n", candidates[i].name);
    }
  }
}

bool vote(string name)
{
  for (int i = 0; i < MAX; i++)
  {
    if (candidates[i].name == name)
    {
      return true;
    };
  }
  return false;
}

int main(int argc, string argv[])
{

  for (int i = 0; i < argc - 1; i++)
  {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
  }

  int number_of_voters = get_int("Number of voters");
  for (int i = 0; i < number_of_voters; i++)
  {
    string name = get_string("Vote:");
    if (vote(name))
    {
      candidates[i].votes += 1;
    }
  }

  print_winner();
}
