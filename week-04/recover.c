#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// bool isJPEG (char buffer[]){
//     return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
// }

int main(int argc, char *argv[])
{
  if (!argv[1])
  {
    printf("Usage: recover [filename.raw]\n");
    return 1;
  }

  // Open memory card
  int BUFFER_SIZE = 512;
  unsigned char buffer[BUFFER_SIZE];
  int counter = 0;
  char *filename = NULL;

  FILE *card = fopen(argv[1], "r");
  FILE *image = fopen("001.jpg", "r");

  // Repeat until end of card
  while (fread(buffer, sizeof buffer, 1, card) == 1)
  {

    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {

      if (image == NULL)
      {

        sprintf(filename, "%03i.jpg", counter);
        printf("%i\n", counter);
        counter++;

        image = fopen(filename, "w");

        fwrite(buffer, BUFFER_SIZE, 1, image);
      }
      else
      {
        fclose(image);
      }
    }
    else
    {

      image = fopen(filename, "a");
      fprintf(image, "%s", buffer);
    }
  }

  if (feof(card))
  {
    // hit end of file
  }
  else
  {
    printf("An error occured...");
  }

  // If stat of new JPEG
  // If first JPEG
  // create file to save jpeg to

  // sprintf(filename, "%03i.jpg", count); // make a new JPEG (###.jpg)

  // FILE *img = fopen(filename, "w"); // start writing

  // fwrite(data, size, number, outptr){
  // data; pointer to bytes to be written
  // size of each element to write
  // number: number of elements to write
  // outptr: FILE * to write to (the file we just opened)
  // }

  // Else

  // close file

  //
  // Else
  // If already found JPEG

  // keep adding to blocks to file
  //

  // Close any remaining files
}
