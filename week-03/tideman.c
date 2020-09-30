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
  for (int i = 0; i < candidate_count; i++)
  {
    if (strcmp(candidates[i], name))
    {
      return i;
    }
  }
  return -1;
}

// // linear search to get index of string in string array
// int get_rank (int candidate_id, int ranks[])   {
//     int rank = 0;
//     for (int i = 0; i < candidate_count; i++) {
//         if (ranks[i] == candidate_id){
//             return rank;
//         }
//     }
//     return -1;
// }

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
    for (int j = i + 1; j < candidate_count; j++)
    {
      preferences[ranks[i]][ranks[j]]++;
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
      int score_for = candidates[i][j];
      int score_against = candidates[j][i];
      if (score_for > 0 && score_for > score_against)
      {
        pairs[pair_count].winner = i;
        pairs[pair_count].loser = j;
        pair_count++;
      }
    }
  }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
  int swap_counter = -1;
  int sorted_to = 0;

  while (swap_counter != 0)
  {
    swap_counter = 0;
    for (int i = 0; i < pair_count - 1; i++)
    {
      int strength_current = pairs[i].winner - pairs[i].loser;
      int strength_next = pairs[i + 1].winner - pairs[i + 1].loser;
      if (strength_next > strength_current)
      {
        pair temporary = pairs[i];
        pairs[i] = pairs[i + 1];
        pairs[i + 1] = temporary;
        swap_counter++;
      }
    }
  }

  // for (int i = 0; i < pair_count; i++){
  //     printf("winner: %i \n", pairs[i].winner);
  //     printf("loswer: %i \n", pairs[i].loser);
  // }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
  for (int i = 0; i < pair_count; i++)
  {
    // if does not create a cycle??
    locked[pairs[i].winner][pairs[i].loser] = true;
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