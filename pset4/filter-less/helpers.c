#include "helpers.h"
#include <math.h>
// Convert image to grayscale

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            int greenVal = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (greenVal > 255)
            {
                greenVal = 255;
            }


            int blueVal = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (blueVal > 255)
            {
                blueVal = 255;
            }


            int redVal = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (redVal > 255)
            {
                redVal = 255;
            }
            image[i][j].rgbtRed = redVal;
            image[i][j].rgbtBlue = blueVal;
            image[i][j].rgbtGreen = greenVal;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swapPixel;
    if (width % 2 == 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < (width / 2); j++)
            {
                swapPixel = image[i][j];
                image[i][j] = image[i][width - (1 + j)];
                image[i][width - (1 + j)] = swapPixel;
            }
        }
    }

    if (width % 2 != 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j <= (width / 2); j++)
            {
                swapPixel = image[i][j];
                image[i][j] = image[i][width - (1 + j)];
                image[i][width - (1 + j)] = swapPixel;
            }
        }
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    //create a copy of original image to save original pixel values
    for (int row = 0; row < height; row++)
	{
        for (int w = 0; w < width; w++)
		{
            imageCopy[row][w].rgbtRed = image[row][w].rgbtRed;
			imageCopy[row][w].rgbtGreen = image[row][w].rgbtGreen;
			imageCopy[row][w].rgbtBlue = image[row][w].rgbtBlue;
		}
	}

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //First case : First Row
            if (i == 0)
            {
                //First corner
                if (j == 0)
                {
                    int redVal = round((imageCopy[0][0].rgbtRed + imageCopy[0][1].rgbtRed + imageCopy[1][0].rgbtRed + imageCopy[1][1].rgbtRed) / 4.0);
                    int greenVal = round((imageCopy[0][0].rgbtGreen + imageCopy[0][1].rgbtGreen + imageCopy[1][0].rgbtGreen + imageCopy[1][1].rgbtGreen) / 4.0);
                    int blueVal = round((imageCopy[0][0].rgbtBlue + imageCopy[0][1].rgbtBlue + imageCopy[1][0].rgbtBlue + imageCopy[1][1].rgbtBlue) / 4.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }

                //Upper side without corners
                else if (j > 0 && j < width - 1)
                {
                    int redVal = round((imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed +
                    imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / 6.0);

                    int greenVal = round((imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen +
                    imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / 6.0);
                    
                    int blueVal = round((imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue +
                    imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / 6.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }

                //Last corner
                else if (j == width - 1)
                {
                    int redVal = round((imageCopy[0][width - 1].rgbtRed + imageCopy[1][width - 1].rgbtRed + imageCopy[0][width - 2].rgbtRed +
                    imageCopy[1][width - 2].rgbtRed) / 4.0);

                    int greenVal = round((imageCopy[0][width - 1].rgbtGreen + imageCopy[1][width - 1].rgbtGreen + imageCopy[1][width - 2].rgbtGreen +
                    imageCopy[0][width - 2].rgbtGreen) / 4.0);

                    int blueVal = round((imageCopy[0][width - 1].rgbtBlue + imageCopy[1][width - 1].rgbtBlue + imageCopy[0][width - 2].rgbtBlue +
                    imageCopy[1][width - 2].rgbtBlue) / 4.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }
            }

            //Second case : Rows between the first and the last row
            else if(i > 0 && i < height - 1)
            {
                //Left side without corners
                if (j == 0)
                {
                    int redVal = round((imageCopy[i - 1][j].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed +
                    imageCopy[i][j + 1].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / 6.0);

                    int greenVal = round((imageCopy[i - 1][j].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i + 1][j].rgbtGreen +
                    imageCopy[i - 1][j + 1].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / 6.0);

                    int blueVal = round((imageCopy[i - 1][j].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i + 1][j].rgbtBlue +
                    imageCopy[i - 1][j + 1].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / 6.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }

                //Right side without corners
                else if (j == height - 1)
                {
                    int redVal = round((imageCopy[i - 1][j].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i - 1][j - 1].rgbtRed +
                    imageCopy[i][j - 1].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed) / 6.0);

                    int greenVal = round((imageCopy[i - 1][j].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i - 1][j - 1].rgbtGreen +
                    imageCopy[i][j - 1].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen) / 6.0);

                    int blueVal = round((imageCopy[i - 1][j].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i - 1][j - 1].rgbtBlue +
                    imageCopy[i][j - 1].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue) / 6.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }

                //Columns in-between
                else
                {
                    int redVal = round((imageCopy[i - 1][j].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i + 1][j].rgbtRed +
                    imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i][j - 1].rgbtRed + imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed +
                    imageCopy[i - 1][j + 1].rgbtRed + imageCopy[i][j + 1].rgbtRed) / 9.0);

                    int greenVal = round((imageCopy[i - 1][j].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i + 1][j].rgbtGreen +
                    imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i][j - 1].rgbtGreen + imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen +
                    imageCopy[i - 1][j + 1].rgbtGreen + imageCopy[i][j + 1].rgbtGreen) / 9.0);

                    int blueVal = round((imageCopy[i - 1][j].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i + 1][j].rgbtBlue +
                    imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i][j - 1].rgbtBlue + imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue +
                    imageCopy[i - 1][j + 1].rgbtBlue + imageCopy[i][j + 1].rgbtBlue) / 9.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }
            }


            //Last case : Last column
            else if (i == height - 1)
            {
                //First corner
                if (j == 0)
                {

                    int redVal = round((imageCopy[height - 1][0].rgbtRed + imageCopy[height - 1][1].rgbtRed + imageCopy[height - 2][0].rgbtRed +
                    imageCopy[height - 2][1].rgbtRed) / 4.0);
                    int greenVal = round((imageCopy[height - 1][0].rgbtGreen + imageCopy[height - 1][1].rgbtGreen + imageCopy[height - 2][0].rgbtGreen +
                    imageCopy[height - 2][1].rgbtGreen) / 4.0);
                    int blueVal = round((imageCopy[height - 1][0].rgbtBlue + imageCopy[height - 1][1].rgbtBlue + imageCopy[height - 2][0].rgbtBlue +
                    imageCopy[height - 2][1].rgbtBlue) / 4.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }

                //Lower side without corners
                else if (j > 0 && j < width - 1)
                {
                    int redVal = round((imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + imageCopy[i - 1][j - 1].rgbtRed +
                    imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed) / 6.0);
                    int greenVal = round((imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen +
                    imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen) / 6.0);
                    int blueVal = round((imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue +
                    imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue) / 6.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }

                //Last corner
                else if (j == width - 1)
                {
                    int redVal = round((imageCopy[height - 1][width - 1].rgbtRed + imageCopy[height - 1][width - 2].rgbtRed +
                    imageCopy[height - 2][width - 1].rgbtRed + imageCopy[height - 2][width - 2].rgbtRed) / 4.0);
                    int greenVal = round((imageCopy[height - 1][width - 1].rgbtGreen + imageCopy[height - 1][width - 2].rgbtGreen +
                    imageCopy[height - 2][width - 1].rgbtGreen + imageCopy[height - 2][width - 2].rgbtGreen) / 4.0);
                    int blueVal = round((imageCopy[height - 1][width - 1].rgbtBlue + imageCopy[height - 1][width - 2].rgbtBlue +
                    imageCopy[height - 2][width - 1].rgbtBlue + imageCopy[height - 2][width - 2].rgbtBlue) / 4.0);

                    image[i][j].rgbtRed = redVal;
			        image[i][j].rgbtGreen = greenVal;
			        image[i][j].rgbtBlue = blueVal;
                }
            }

        }
    }
return;
}
