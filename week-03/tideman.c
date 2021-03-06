#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
  int winner;
  int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{

  // Check for invalid usage
  if (argc < 2)
  {
    printf("Usage: tideman [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX)
  {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }

  for (int i = 0; i < candidate_count; i++)
  {
    candidates[i] = argv[i + 1];
  }

  // Clear graph of locked in pairs
  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = 0; j < candidate_count; j++)
    {
      locked[i][j] = false;
    }
  }

  pair_count = 0;
  int voter_count = get_int("Number of voters: ");

  // Query for votes
  for (int i = 0; i < voter_count; i++)
  {
    // ranks[i] is voter's ith preference
    int ranks[candidate_count];

    // Query for each rank
    for (int j = 0; j < candidate_count; j++)
    {
      string name = get_string("Rank %i: ", j + 1);

      if (!vote(j, name, ranks))
      {
        printf("Invalid vote.\n");
        return 3;
      }
    }

    record_preferences(ranks);

    printf("\n");
  }

  add_pairs();
  sort_pairs();
  lock_pairs();
  print_winner();
  return 0;
}

// Linear search to get index of string in string array
int get_index_of_candidate(string name)
{
  for (int i = 0; i < candidate_count; ++i)
  {
    if (strcmp(candidates[i], name) == 0)
    {
      return i;
    }
  }
  return -1;
}

// // linear search to get index of string in string array
int get_rank(int candidate_id, int ranks[])
{

  for (int i = 0; i < candidate_count; i++)
  {
    if (ranks[i] == candidate_id)
    {
      return i;
    }
  }
  return -1;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

  int candidate_index = get_index_of_candidate(name);

  if (candidate_index > -1)
  {
    ranks[rank] = candidate_index;
    return true;
  }
  return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = 0; j < candidate_count; j++)
    {

      if (get_rank(i, ranks) < get_rank(j, ranks))
      {
        preferences[i][j] += 1;
      }
    }
  }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = 0; j < candidate_count; j++)
    {
      int score_for = preferences[i][j];
      int score_against = preferences[j][i];

      if (score_for > 0 && score_for > score_against)
      {
        pairs[pair_count].winner = i;
        pairs[pair_count].loser = j;
        pair_count++;
      }
    }
  }
}

// Get difference between winning and losing scores
int get_margin(int winner, int loser)
{
  return preferences[winner][loser] - preferences[loser][winner];
}

// Sort pairs in decreasing order by strength of victory - bubble sort
void sort_pairs(void)
{
  int swap_counter = -1;

  while (swap_counter != 0)
  {
    swap_counter = 0;
    for (int i = 0; i < pair_count - 1; i++)
    {

      int margin = get_margin(pairs[i].winner, pairs[i].loser);
      int next_margin = get_margin(pairs[i + 1].winner, pairs[i + 1].loser);

      if (next_margin > margin)
      {
        pair temporary = pairs[i];
        pairs[i] = pairs[i + 1];
        pairs[i + 1] = temporary;
        swap_counter++;
      }
    }
  }
}

// Determine if adding a graph link will cycle
bool will_cycle(int winner, int loser, int from)
{

  if (from == loser)
  {
    return true;
  }

  for (int i = 0; i < candidate_count; i++)
  {
    if ((locked[loser][i]) == true && will_cycle(loser, i, from))
    {
      return will_cycle(loser, i, from);
    }
  }

  return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
  for (int i = 0; i < pair_count; i++)
  {
    if (!will_cycle(pairs[i].winner, pairs[i].loser, pairs[i].winner))
    {
      locked[pairs[i].winner][pairs[i].loser] = true;
    }
  }
}

// Print the winner of the election
void print_winner(void)
{
  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = 0; j < candidate_count; j++)
    {
      if (!locked[j][i])
      {
        printf("%s\n", candidates[i]);
        break;
      }
    }
  }
}
