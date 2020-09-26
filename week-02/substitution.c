#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int ALPHABET_LENGTH = 26;

bool has_duplicates(string key, int length)
{
  for (int i = 0; i < length; i++)
  {
    for (int j = i + 1; j < length; j++)
    {
      if (key[i] == key[j])
        return true;
    }
  }
  return false;
}

bool is_alphabetic_only(string key, int length)
{
  for (int i = 0; i < length; i++)
  {
    if (!isalpha(key[i]))
      return false;
  }
  return true;
}

bool key_validator(string key)
{
  int length = strlen(key);
  bool valid = false;

  if (length != ALPHABET_LENGTH)
  {
    printf("%s", "Key must only contain 26 characters\n");
  }
  else if (!is_alphabetic_only(key, length))
  {
    printf("%s", "Key must only contain alphabet characters\n");
  }
  else if (has_duplicates(key, length))
  {
    printf("%s", "Key must not contain repeated characters\n");
  }
  else
  {
    valid = true;
  }

  return valid;
}

char translate(char character, string key)
{
  char letter = toupper(character);
  int index = strchr(ALPHABET, letter) - ALPHABET;
  return key[index];
}

string encipher(string message, string key)
{
  int length = strlen(message);
  for (int i = 0; i < length; i++)
  {
    char token = message[i];
    if (islower(token))
    {
      message[i] = tolower(translate(token, key));
    }
    else if (isupper(token))
    {
      message[i] = toupper(translate(token, key));
    }
  }
  return message;
}

int main(int argc, string argv[])
{

  string key = argv[1];

  if (!key)
  {
    printf("Usage: ./substitution KEY\n");
    return 1;
  }
  else
  {
    if (key_validator(key))
    {
      string message = get_string("Message:");
      printf("ciphertext: %s\n", encipher(message, key));
    }
    else
    {
      return 1;
    }
  }
}