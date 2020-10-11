// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
  char word[LENGTH + 1];
  struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
  node *nodePointer = table[hash(word)];

  while (nodePointer != NULL)
  {
    if (strcasecmp(nodePointer->word, word) == 0)
    {
      return true;
    }
    nodePointer = nodePointer->next;
  }

  return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
  char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  int index = -1;
  for (int i = 0; i < N; i++)
  {
    if (word[0] == alphabet[i])
    {
      index = i;
    }
  }
  return index;

  // char letter = tolower(word[0]);
  // int index = strcspn(ALPHABET, &letter);
  // return index > -1 ? index : -1;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

  // open file
  FILE *file = fopen(dictionary, "r");
  if (file == NULL)
  {
    return false;
  }

  // initialise table
  for (int i = 0; i < N; i++)
  {
    table[i] = NULL;
  }

  char word[LENGTH + 1];

  //  while(i < size  &&  fscanf(m,"%d", &data[i++]) == 1);
  while (fscanf(file, "%s\n", word) == 1)
  {

    // create node
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL)
    {
      return false;
    }

    // copy word into node
    strcpy(newNode->word, word);

    // get pointer to head
    node *head = table[hash(word)];

    // add to front of list
    if (head == NULL)
    {
      head = newNode;
      newNode->next = NULL;
    }
    else
    {
      newNode->next = head->next;
      head = newNode;
    }
  }

  fclose(file);

  return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
  int counter = 0;
  for (int i = 0; i < N; i++)
  {
    node *nodePointer = table[i];
    while (nodePointer != NULL)
    {
      counter++;
      nodePointer = nodePointer->next;
    }
  }
  return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
  for (int i = 0; i < N; i++)
  {
    node *nodePointer = table[i];
    while (nodePointer != NULL)
    {
      node *temp = nodePointer;
      nodePointer = nodePointer->next;
      free(temp);
    }
    table[i] = NULL;
  }
  return true;
}
