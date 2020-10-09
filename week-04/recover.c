#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isJPEG(unsigned char buffer[])
{
  return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}

int main(int argc, char *argv[])
{
  if (!argv[1])
  {
    printf("Usage: recover [cardname.raw]\n");
    return 1;
  }

  int BUFFER_SIZE = 512;
  unsigned char buffer[BUFFER_SIZE];
  char filename[10];
  int counter = 0;

  FILE *card = fopen(argv[1], "r");
  FILE *image = NULL;

  while (!feof(card) && fread(&buffer, sizeof buffer, 1, card) == 1)
  {

    if (isJPEG(buffer))
    {

      if (image)
      {
        fclose(image);
      }

      sprintf(filename, "%03i.jpg", counter);
      image = fopen(filename, "w");
      fwrite(&buffer, sizeof buffer, 1, image);
      counter++;
    }
    else if (image)
    {
      fwrite(&buffer, sizeof buffer, 1, image);
    }
  }

  fclose(card);
  fclose(image);
}
