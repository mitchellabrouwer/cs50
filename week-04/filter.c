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

      int average = round((red + green + blue) / 3.0);

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

  RGBTRIPLE newImage[height][width];

  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {

      int sumRed = 0;
      int sumBlue = 0;
      int sumGreen = 0;
      float squares = 0;

      for (int innerRow = -1; innerRow <= 1; innerRow++)
      {
        for (int innerColumn = -1; innerColumn <= 1; innerColumn++)
        {

          int x = row + innerRow;
          int y = column + innerColumn;

          if (y > -1 && y < height && x > -1 && x < width)
          {

            sumRed += image[y][x].rgbtRed;
            sumGreen += image[y][x].rgbtGreen;
            sumBlue += image[y][x].rgbtBlue;
            squares++;
          }
        }
      }

      newImage[row][column].rgbtRed = round(sumRed / squares);
      newImage[row][column].rgbtGreen = round(sumGreen / squares);
      newImage[row][column].rgbtBlue = round(sumBlue / squares);
    }
  }

  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      image[row][column].rgbtRed = newImage[row][column].rgbtRed;
      image[row][column].rgbtGreen = newImage[row][column].rgbtGreen;
      image[row][column].rgbtBlue = newImage[row][column].rgbtBlue;
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

  int inner_grid_size = 9;
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
      for (int d = 0; d < inner_grid_size; d++)
      {
        int gridRow = row + y[d];
        int gridColumn = column + x[d];

        if (gridRow > -1 && gridRow < height && gridColumn > -1 && gridColumn < width)
        {

          red_gx += image[gridRow][gridColumn].rgbtRed * gx[d];
          red_gy += image[gridRow][gridColumn].rgbtRed * gy[d];

          green_gx += image[gridRow][gridColumn].rgbtGreen * gx[d];
          green_gy += image[gridRow][gridColumn].rgbtGreen * gy[d];

          blue_gx += image[gridRow][gridColumn].rgbtBlue * gx[d];
          blue_gy += image[gridRow][gridColumn].rgbtBlue * gy[d];
        }
      }

      // printf("redgx %i \n", red_gx);
      // printf("red gy %i, \n", red_gy);
      // printf("blue gx %i, \n", blue_gx);
      // printf("blue gy %i, \n", blue_gy);
      // printf("green gx %i, \n", green_gx);
      // printf("green gy %i, \n", green_gy);

      image[row][column].rgbtRed = (red_gx * red_gx) + (red_gy * red_gy);
      image[row][column].rgbtBlue = (blue_gx * blue_gx) + (blue_gy * blue_gy);
      image[row][column].rgbtGreen = (green_gx * green_gx) + (green_gy * green_gy);
      // image[row][column].rgbtRed = red_gx;
      // image[row][column].rgbtGreen = (green_gx * green_gx) +(green_gy * green_gy);
      // image[row][column].rgbtBlue = red_gy;

      // printf("%hhu red: \n", image[row][column].rgbtRed);
      // printf("%hhu blue: \n", image[row][column].rgbtBlue);
      // printf("%hhu green: \n",  image[row][column].rgbtGreen);

      // printf("%li red: \n", lround(sqrt((red_gx * red_gx) + (red_gy * red_gy))));
      // printf("%li blue: \n", lround(sqrt((blue_gx * blue_gx) + (blue_gy * blue_gy) )));
      // printf("%li green: \n", lround(sqrt((green_gx * green_gx) +(green_gy * green_gy)) ));
    }
  }

  return;
}
