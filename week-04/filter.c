#include <stdio.h>
#include "helpers.h"
#include "math.h"

int cap(int color)
{
  return color > 255 ? 255 : color;
}

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

      image[row][column].rgbtRed = cap(round(sumRed / adjacent_count));
      image[row][column].rgbtGreen = cap(round(sumGreen / adjacent_count));
      image[row][column].rgbtBlue = cap(round(sumBlue / adjacent_count));
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

  int g_size = 9;
  int x[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
  int y[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

  int gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
  int gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

  // loop image grid
  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {

      int red_gx = 0;
      int red_gy = 0;

      int blue_gx = 0;
      int blue_gy = 0;

      int green_gx = 0;
      int green_gy = 0;

      // loop multiplier grid
      for (int d = 0; d < g_size; d++)
      {
        int gridRow = row + y[d];
        int gridColumn = column + x[d];

        if (gridRow > 0 && gridRow < height - 1 && gridColumn > 0 && gridColumn < width - 1)
        {

          red_gx += image[gridRow][gridColumn].rgbtRed * gx[d];
          red_gy += image[gridRow][gridColumn].rgbtRed * gy[d];

          blue_gx += image[gridRow][gridColumn].rgbtBlue * gx[d];
          blue_gy += image[gridRow][gridColumn].rgbtBlue * gy[d];

          red_gx += image[gridRow][gridColumn].rgbtGreen * gx[d];
          red_gy += image[gridRow][gridColumn].rgbtGreen * gy[d];
        }
      }

      printf("redgx %i \n", red_gx);
      printf("red gy %i, \n", red_gy);
      printf("blue gx %i, \n", blue_gx);
      printf("blue gy %i, \n", blue_gy);
      printf("green gx %i, \n", green_gx);
      printf("green gy %i, \n", green_gy);

      image[row][column].rgbtRed = cap(round(sqrt((red_gx * red_gx) + (red_gy * red_gy))));
      image[row][column].rgbtBlue = cap(round(sqrt((blue_gx * blue_gx) + (blue_gy * blue_gy))));
      image[row][column].rgbtGreen = cap(round(sqrt((green_gx * green_gx) + (green_gy * green_gy))));

      // printf("%i red: \n",cap(round(sqrt((red_gx * red_gx) + (red_gy * red_gy)))));
      // printf("%i blue: \n", cap(round(sqrt((blue_gx * blue_gx) + (blue_gy * blue_gy) ))));
      // printf("%i green: \n", cap(round(sqrt((green_gx * green_gx) +(green_gy * green_gy)) )));
    }
  }

  return;
}
