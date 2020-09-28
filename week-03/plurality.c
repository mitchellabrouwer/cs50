#include <stdio.h>
#include <cs50.h>
#include <string.h>

const int MAX = 9;

typedef struct
{
  string name;
  int votes;
} candidate;

candidate candidates[9];

int candidate_count;

int get_maximum_vote(void)
{
  int max = candidates[0].votes;
  for (int i = 1; i < candidate_count; i++)
  {
    if (candidates[i].votes > max)
    {
      max = candidates[i].votes;
    }
  }
  return max;
}

void print_winner(void)
{
  int maximum = get_maximum_vote();

  for (int i = 0; i < candidate_count; i++)
  {
    if (candidates[i].votes == maximum)
    {
      printf("%s\n", candidates[i].name);
    }
  }
}

bool vote(string name)
{
  for (int i = 0; i < candidate_count; i++)
  {
    if (strcmp(candidates[i].name, name) == 0)
    {
      candidates[i].votes++;
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

  candidate_count = get_int("Number of voters: ");
  for (int i = 0; i < candidate_count; i++)
  {
    string name = get_string("Vote: ");
    vote(name);
  }

  print_winner();
}
