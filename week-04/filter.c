#include <stdio.h>
#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      int red = image[row][column].rgbtRed;
      int green = image[row][column].rgbtGreen;
      int blue = image[row][column].rgbtBlue;

      int average = round((red + green + blue) / 3);

      image[row][column].rgbtRed = average;
      image[row][column].rgbtGreen = average;
      image[row][column].rgbtBlue = average;
    }
  }

  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  int halfway = floor((width) / 2);

  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < halfway; column++)
    {

      int reflected_index = width - 1 - column;

      RGBTRIPLE temporary = image[row][column];
      image[row][column] = image[row][reflected_index];
      image[row][reflected_index] = temporary;
    }
  }

  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

  int adjacent_count = 8;
  int x[8] = {0, 1, -1, 0, -1, 1, -1, 1};
  int y[8] = {1, 0, 0, -1, 1, -1, -1, 1};

  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {

      int sumRed = 0;
      int sumBlue = 0;
      int sumGreen = 0;

      for (int d = 0; d < adjacent_count; d++)
      {

        int adjacentRow = row + y[d];
        int adjacentColumn = column + y[d];

        if (adjacentRow > 0 && adjacentRow < height - 1 && adjacentColumn > 0 && adjacentColumn < width - 1)
        {
          sumRed += image[adjacentRow][adjacentColumn].rgbtRed;
          sumBlue += image[adjacentRow][adjacentColumn].rgbtBlue;
          sumGreen += image[adjacentRow][adjacentColumn].rgbtGreen;
        }
      }

      image[row][column].rgbtRed = round(sumRed / adjacent_count);
      image[row][column].rgbtGreen = round(sumGreen / adjacent_count);
      image[row][column].rgbtBlue = round(sumBlue / adjacent_count);
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
  return;
}
