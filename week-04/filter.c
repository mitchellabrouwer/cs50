#include <stdio.h>
#include "helpers.h"
#include "math.h"

// Cap rgb value at 255
int cap(int color)
{
  return color > 255 ? 255 : color;
}

// Replace image with new image
void update_image(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE newImage[height][width])
{
  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      image[row][column].rgbtRed = newImage[row][column].rgbtRed;
      image[row][column].rgbtGreen = newImage[row][column].rgbtGreen;
      image[row][column].rgbtBlue = newImage[row][column].rgbtBlue;
    }
  }
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

          int y = row + innerRow;
          int x = column + innerColumn;

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

  update_image(height, width, image, newImage);

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

  int gx[3][3] = {
      {-1, 0, 1},
      {-2, 0, 2},
      {-1, 0, 1}};

  int gy[3][3] = {
      {-1, -2, -1},
      {0, 0, 0},
      {1, 2, 1}};

  RGBTRIPLE newImage[height][width];

  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {

      long gxRed = 0, gxGreen = 0, gxBlue = 0;
      long gyRed = 0, gyGreen = 0, gyBlue = 0;

      for (int innerRow = -1; innerRow <= 1; innerRow++)
      {
        for (int innerColumn = -1; innerColumn <= 1; innerColumn++)
        {

          int y = row + innerRow;
          int x = column + innerColumn;
          int gRow = 1 + innerRow;
          int gColumn = 1 + innerColumn;

          if (y > -1 && y < height && x > -1 && x < width)
          {

            gxRed += image[y][x].rgbtRed * gx[gRow][gColumn];
            gyRed += image[y][x].rgbtRed * gy[gRow][gColumn];

            gxGreen += image[y][x].rgbtGreen * gx[gRow][gColumn];
            gyGreen += image[y][x].rgbtGreen * gy[gRow][gColumn];

            gxBlue += image[y][x].rgbtBlue * gx[gRow][gColumn];
            gyBlue += image[y][x].rgbtBlue * gy[gRow][gColumn];
          }
        }
      }

      newImage[row][column].rgbtRed = cap((int)round(sqrt((gxRed * gxRed) + (gyRed * gyRed))));
      newImage[row][column].rgbtGreen = cap((int)round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen))));
      newImage[row][column].rgbtBlue = cap((int)round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue))));
    }
  }

  update_image(height, width, image, newImage);

  return;
}
