#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (uint32_t row = 0; row < height; ++row)
    {
        for (uint32_t column = 0; column < width; ++column)
        {
            uint8_t red = image[row][column].rgbtRed;
            uint8_t green = image[row][column].rgbtGreen;
            uint8_t blue = image[row][column].rgbtBlue;

            double COLOURS = 3.0;

            uint8_t average = round(((red + green + blue) / COLOURS));

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
    for (uint32_t row = 0; row < height; ++row)
    {
        RGBTRIPLE temporary[width];

        for (uint32_t column = 0; column < width; ++column)
        {
            temporary[column] = image[row][column];

            image[row][column] = temporary[column];
        }

        const uint8_t CONSTANT = 1;

        for (uint32_t reverse = 0; reverse < width; ++reverse)
        {
            image[row][reverse] = temporary[width - CONSTANT - reverse];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width];

    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
            uint32_t sum_red = 0;
            uint32_t sum_green = 0;
            uint32_t sum_blue = 0;

            float counter = 0.00;

            for (int matrix_row = -1; matrix_row < 2; ++matrix_row)
            {
                for (int matrix_column = -1; matrix_column < 2; ++matrix_column)
                {
                    if (row + matrix_row < 0 || row + matrix_row > height -1 || column + matrix_column < 0 || column + matrix_column > width - 1)
                    {
                        continue;
                    }

                    sum_red += image[row + matrix_row][column + matrix_column].rgbtRed;
                    sum_green += image[row + matrix_row][column + matrix_column].rgbtGreen;
                    sum_blue += image[row + matrix_row][column + matrix_column].rgbtBlue;

                    counter++;
                }
            }

            temporary[row][column].rgbtRed = round(sum_red / counter);
            temporary[row][column].rgbtGreen = round(sum_green / counter);
            temporary[row][column].rgbtBlue = round(sum_blue / counter);
        }
    }

    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
            image[row][column].rgbtRed = temporary[row][column].rgbtRed;
            image[row][column].rgbtGreen = temporary[row][column].rgbtGreen;
            image[row][column].rgbtBlue = temporary[row][column].rgbtBlue;
        }
    }
    return;
}

// Detect edges using sobel operator
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    const int gX[3][3] =
    {
        {+1, 0, -1},
        {+2, 0, -2},
        {+1, 0, -1}
    };

    const int gY[3][3] =
    {
        {+1, +2, +1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    RGBTRIPLE temporary[height][width];

    for (uint32_t row = 0; row < height; ++row)
    {
        for (uint32_t column = 0; column < width; ++column)
        {
            uint32_t gX_sum_red = 0;
            uint32_t gX_sum_green = 0;
            uint32_t gX_sum_blue = 0;

            uint32_t gY_sum_red = 0;
            uint32_t gY_sum_green = 0;
            uint32_t gY_sum_blue = 0;

            for (int matrix_row = -1; matrix_row < 2; ++matrix_row)
            {
                for (int matrix_column = -1; matrix_column < 2; ++matrix_column)
                {
                    if (row + matrix_row < 0 || row + matrix_row > height -1 || column + matrix_column < 0 || column + matrix_column > width - 1)
                    {
                        continue;
                    }

                    gX_sum_red += image[row + matrix_row][column + matrix_column].rgbtRed * gX[matrix_row + 1][matrix_column +1];
                    gX_sum_green += image[row + matrix_row][column + matrix_column].rgbtGreen * gX[matrix_row + 1][matrix_column +1];
                    gX_sum_blue += image[row + matrix_row][column + matrix_column].rgbtBlue * gX[matrix_row + 1][matrix_column +1];

                    gY_sum_red += image[row + matrix_row][column + matrix_column].rgbtRed * gY[matrix_row + 1][matrix_column +1];
                    gY_sum_green += image[row + matrix_row][column + matrix_column].rgbtGreen * gY[matrix_row + 1][matrix_column +1];
                    gY_sum_blue += image[row + matrix_row][column + matrix_column].rgbtBlue * gY[matrix_row + 1][matrix_column +1];

                }
            }
            temporary[row][column].rgbtRed = fmin(round(sqrt(gX_sum_red * gX_sum_red + gY_sum_red * gY_sum_red)), 255);
            temporary[row][column].rgbtGreen = fmin(round(sqrt(gX_sum_green * gX_sum_green + gY_sum_green * gY_sum_green)), 255);
            temporary[row][column].rgbtBlue = fmin(round(sqrt(gX_sum_blue * gX_sum_blue + gY_sum_blue * gY_sum_blue)), 255);
        }
    }

    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
            image[row][column].rgbtRed = temporary[row][column].rgbtRed;
            image[row][column].rgbtBlue = temporary[row][column].rgbtBlue;
            image[row][column].rgbtGreen = temporary[row][column].rgbtGreen;
        }
    }

    return;
}