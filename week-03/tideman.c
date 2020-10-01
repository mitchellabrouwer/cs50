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

// linear search to get index of string in string array
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

// Sort pairs in decreasing order by strength of victory - bubble sort
void sort_pairs(void)
{
  int swap_counter = -1;

  while (swap_counter != 0)
  {
    swap_counter = 0;
    for (int i = 0; i < pair_count - 1; i++)
    {

      // get winners and losers of current and next
      int winner = pairs[i].winner;
      int loser = pairs[i].loser;
      int next_winner = pairs[i + 1].winner;
      int next_loser = pairs[i + 1].loser;

      // calculate margins
      int margin = preferences[winner][loser] - preferences[loser][winner];
      int next_margin = preferences[next_winner][next_loser] - preferences[next_loser][next_winner];

      // if bigger margin swap
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

bool is_unique(int arr[], int length)
{
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length; j++)
    {
      printf("row %i \n", arr[i]);
      printf("col %i \n", arr[j]);
      // if (i != j && arr[i] == arr[j]) {
      //     printf("not unique");
      //     return false;
      // }
    }
  }
  printf("unique");
  return true;
}

bool has_cycle()
{
  int length = 0;
  int row_indexes[candidate_count];
  int col_indexes[candidate_count];

  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = 0; j < candidate_count; j++)
    {
      if (locked[i][j] == true)
      {
        // printf("row %i \n", i);
        // printf("col %i \n", j)
        row_indexes[length] = i;
        col_indexes[length] = j;

        length++;
      }
    }
  }

  // for (int i = 0; i < length; i++) {
  //     printf("row %i \n", row_indexes[length]);
  //     printf("col %i \n", col_indexes[length]);
  // }

  if (is_unique(row_indexes, length) && is_unique(col_indexes, length))
  {
    // printf("true");
    return true;
  }
  else
  {
    return false;
  }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
  for (int i = 0; i < pair_count; i++)
  {
    locked[pairs[i].winner][pairs[i].loser] = true;
    if (has_cycle())
    {
      locked[pairs[i].winner][pairs[i].loser] = false;
    }
  }
}

// Print the winner of the election
void print_winner(void)
{

  int most_edges = 0;
  string winner;

  for (int i = 0; i < candidate_count; i++)
  {
    int edges = 0;
    for (int j = 0; j < candidate_count; j++)
    {
      if (locked[i][j])
      {
        edges++;
      }
      if (edges > most_edges)
      {
        most_edges = edges;
        winner = candidates[i];
      }
    }
  }

  printf("%s", winner);
}