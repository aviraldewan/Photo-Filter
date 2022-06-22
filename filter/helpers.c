#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calucate average and round it
            avg = round(((float)image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            //Assign the average value
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
    int t_red = 0;
    int t_green = 0;
    int t_blue = 0;
    int tb = 0;
    int tg = 0;
    int tr = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            t_blue = image[i][j].rgbtBlue;
            t_green = image[i][j].rgbtGreen;
            t_red = image[i][j].rgbtRed;
            //Calc temp. blue
            tb = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * t_blue);
            if (tb > 255)
            {
                tb = 255;
            }
            image[i][j].rgbtBlue = tb;
            //calc temp green
            tg = round(0.349 * image[i][j].rgbtRed + 0.686 * t_green + 0.168 * t_blue);
            if (tg > 255)
            {
                tg = 255;
            }
            image[i][j].rgbtGreen = tg;
            //calc temp red
            tr = round(0.393 * t_red + 0.769 * t_green + 0.189 * t_blue);
            if (tr > 255)
            {
                tr = 255;
            }
            image[i][j].rgbtRed = tr;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int t_blue = 0;
    int t_green = 0;
    int t_red = 0;
    int w = width - 1;

    for (int i = 0; i < height; i++)
    {
        //iterate till halp width
        for (int j = 0; j < width / 2; j++)
        {
            //exchange blue value
            t_blue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][w - j].rgbtBlue;
            image[i][w - j].rgbtBlue = t_blue;

            //exchange green value
            t_green = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][w - j].rgbtGreen;
            image[i][w - j].rgbtGreen = t_green;

            //exchange red value
            t_red = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][w - j].rgbtRed;
            image[i][w - j].rgbtRed = t_red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int avgr1 = 0;
    int avgg1 = 0;
    int avgb1 = 0;
    int avgr2 = 0;
    int avgg2 = 0;
    int avgb2 = 0;
    int avgr3 = 0;
    int avgg3 = 0;
    int avgb3 = 0;
    int avgr = 0;
    int avgg = 0;
    int avgb = 0;

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            //corner 1st pixel and 1st row
            if (k == 0 && i == 0)
            {
                avgb1 = (image[i][k].rgbtBlue + image[i][k + 1].rgbtBlue);
                avgb2 = (image[i + 1][k].rgbtBlue + image[i + 1][k + 1].rgbtBlue);
                avgg1 = (image[i][k].rgbtGreen + image[i][k + 1].rgbtGreen);
                avgg2 = (image[i + 1][k].rgbtGreen + image[i + 1][k + 1].rgbtGreen);
                avgr1 = (image[i][k].rgbtRed + image[i][k + 1].rgbtRed);
                avgr2 = (image[i + 1][k].rgbtRed + image[i + 1][k + 1].rgbtRed);

                avgr = round((avgr1 + avgr2)  / 4.0);
                avgg = round((avgg1 + avgg2) / 4.0);
                avgb = round((avgb1 + avgb2)  / 4.0);

                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
            //corner last pixel and last row
            if (k == width - 1 && i == 0)
            {
                avgb1 = (image[i][k].rgbtBlue + image[i][k - 1].rgbtBlue);
                avgb2 = (image[i + 1][k].rgbtBlue + image[i + 1][k - 1].rgbtBlue);
                avgg1 = (image[i][k].rgbtGreen + image[i][k - 1].rgbtGreen);
                avgg2 = (image[i + 1][k].rgbtGreen + image[i + 1][k - 1].rgbtGreen);
                avgr1 = (image[i][k].rgbtRed + image[i][k - 1].rgbtRed);
                avgr2 = (image[i + 1][k].rgbtRed + image[i + 1][k - 1].rgbtRed);

                avgr = round((avgr1 + avgr2)  / 4.0);
                avgg = round((avgg1 + avgg2)  / 4.0);
                avgb = round((avgb1 + avgb2)  / 4.0);

                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
            //corner last pixel and last row
            if (k == width - 1 && i == height - 1)
            {
                avgb1 = (image[i][k].rgbtBlue + image[i][k - 1].rgbtBlue);
                avgb2 = (image[i - 1][k].rgbtBlue + image[i - 1][k - 1].rgbtBlue);
                avgg1 = (image[i][k].rgbtGreen + image[i][k - 1].rgbtGreen);
                avgg2 = (image[i - 1][k].rgbtGreen + image[i - 1][k - 1].rgbtGreen);
                avgr1 = (image[i][k].rgbtRed + image[i][k - 1].rgbtRed);
                avgr2 = (image[i - 1][k].rgbtRed + image[i - 1][k - 1].rgbtRed);

                avgr = round((avgr1 + avgr2)  / 4.0);
                avgg = round((avgg1 + avgg2)  / 4.0);
                avgb = round((avgb1 + avgb2)  / 4.0);

                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
            //corner 1st pixel and last row
            if (k == 0 && i == height - 1)
            {
                avgb1 = (image[i][k].rgbtBlue + image[i][k + 1].rgbtBlue);
                avgb2 = (image[i - 1][k].rgbtBlue + image[i - 1][k + 1].rgbtBlue);
                avgg1 = (image[i][k].rgbtGreen + image[i][k + 1].rgbtGreen);
                avgg2 = (image[i - 1][k].rgbtGreen + image[i - 1][k + 1].rgbtGreen);
                avgr1 = (image[i][k].rgbtRed + image[i][k + 1].rgbtRed);
                avgr2 = (image[i - 1][k].rgbtRed + image[i - 1][k + 1].rgbtRed);

                avgr = round((avgr1 + avgr2)  / 4.0);
                avgg = round((avgg1 + avgg2)  / 4.0);
                avgb = round((avgb1 + avgb2)  / 4.0);

                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
            //1st row
            if (i == 0 && k >= 1 && k <= width - 2)
            {
                avgb1 = (image[i][k].rgbtBlue + image[i][k + 1].rgbtBlue + image[i][k - 1].rgbtBlue);
                avgb2 = (image[i + 1][k].rgbtBlue + image[i + 1][k + 1].rgbtBlue + image[i + 1][k - 1].rgbtBlue);
                avgg1 = (image[i][k].rgbtGreen + image[i][k + 1].rgbtGreen + image[i][k - 1].rgbtGreen);
                avgg2 = (image[i + 1][k].rgbtGreen + image[i + 1][k + 1].rgbtGreen + image[i + 1][k - 1].rgbtGreen);
                avgr1 = (image[i][k].rgbtRed + image[i][k + 1].rgbtRed + image[i][k - 1].rgbtRed);
                avgr2 = (image[i + 1][k].rgbtRed + image[i + 1][k + 1].rgbtRed + image[i + 1][k - 1].rgbtRed);

                avgr = round((avgr1 + avgr2) / 6.0);
                avgg = round((avgg1 + avgg2) / 6.0);
                avgb = round((avgb1 + avgb2) / 6.0);

                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
            //last row
            if (i == height - 1 && k >= 1 && k <= width - 2)
            {
                avgb1 = (image[i][k].rgbtBlue + image[i][k + 1].rgbtBlue + image[i][k - 1].rgbtBlue);
                avgb2 = (image[i - 1][k].rgbtBlue + image[i - 1][k + 1].rgbtBlue + image[i - 1][k - 1].rgbtBlue);
                avgg1 = (image[i][k].rgbtGreen + image[i][k + 1].rgbtGreen + image[i][k - 1].rgbtGreen);
                avgg2 = (image[i - 1][k].rgbtGreen + image[i - 1][k + 1].rgbtGreen + image[i - 1][k - 1].rgbtGreen);
                avgr1 = (image[i][k].rgbtRed + image[i][k + 1].rgbtRed + image[i][k - 1].rgbtRed);
                avgr2 = (image[i - 1][k].rgbtRed + image[i - 1][k + 1].rgbtRed + image[i - 1][k - 1].rgbtRed);

                avgr = round((avgr1 + avgr2) / 6.0);
                avgg = round((avgg1 + avgg2) / 6.0);
                avgb = round((avgb1 + avgb2) / 6.0);

                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
            //middle pixel
            if (i >= 1 && i <= height - 2 && k >= 1 && k <= width - 2)
            {
                avgb1 = (image[i][k].rgbtBlue + image[i][k + 1].rgbtBlue + image[i][k - 1].rgbtBlue);
                avgb2 = (image[i + 1][k].rgbtBlue + image[i + 1][k + 1].rgbtBlue + image[i + 1][k - 1].rgbtBlue);
                avgb3 = (image[i - 1][k].rgbtBlue + image[i - 1][k + 1].rgbtBlue + image[i - 1][k - 1].rgbtBlue);
                avgg1 = (image[i][k].rgbtGreen + image[i][k + 1].rgbtGreen + image[i][k - 1].rgbtGreen);
                avgg2 = (image[i + 1][k].rgbtGreen + image[i + 1][k + 1].rgbtGreen + image[i + 1][k - 1].rgbtGreen);
                avgg3 = (image[i - 1][k].rgbtGreen + image[i - 1][k + 1].rgbtGreen + image[i - 1][k - 1].rgbtGreen);
                avgr1 = (image[i][k].rgbtRed + image[i][k + 1].rgbtRed + image[i][k - 1].rgbtRed);
                avgr2 = (image[i + 1][k].rgbtRed + image[i + 1][k + 1].rgbtRed + image[i + 1][k - 1].rgbtRed);
                avgr3 = (image[i - 1][k].rgbtRed + image[i - 1][k + 1].rgbtRed + image[i - 1][k - 1].rgbtRed);

                avgr = round((avgr1 + avgr2 + avgr3) / 9.0);
                avgg = round((avgg1 + avgg2 + avgg3) / 9.0);
                avgb = round((avgb1 + avgb2 + avgb3) / 9.0);

                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
            //edge 1st pixel
            if (k == 0 && i >= 1 && i <= height - 2)
            {
                //sum of current and next pixel's RGB values
                avgr1 = (image[i][k].rgbtRed + image[i][k + 1].rgbtRed);
                avgg1 = (image[i][k].rgbtGreen + image[i][k + 1].rgbtGreen);
                avgb1 = (image[i][k].rgbtBlue + image[i][k + 1].rgbtBlue);
                //sum of current and next pixel's RGB values of next line
                avgr2 = (image[i + 1][k].rgbtRed + image[i + 1][k + 1].rgbtRed);
                avgg2 = (image[i + 1][k].rgbtGreen + image[i + 1][k + 1].rgbtGreen);
                avgb2 = (image[i + 1][k].rgbtBlue + image[i + 1][k + 1].rgbtBlue);
                //Sum of current and next pixel's RGB values of previous line
                avgr3 = (image[i - 1][k].rgbtRed + image[i - 1][k + 1].rgbtRed);
                avgg3 = (image[i - 1][k].rgbtGreen + image[i - 1][k + 1].rgbtGreen);
                avgb3 = (image[i - 1][k].rgbtBlue + image[i - 1][k + 1].rgbtBlue);

                //Take out average of all the color values
                avgr = round((avgr1 + avgr2 + avgr3) / 6.0);
                avgg = round((avgg1 + avgg2 + avgg3) / 6.0);
                avgb = round((avgb1 + avgb2 + avgb3) / 6.0);

                //Assigns the avg color values to the img in buffer
                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
            //edge last pixel
            if (k == width - 1 && i >= 1 && i <= height - 2)
            {
                //Sum of current and previous pixel's RGB values
                avgr1 = (image[i][k].rgbtRed + image[i][k - 1].rgbtRed);
                avgg1 = (image[i][k].rgbtGreen + image[i][k - 1].rgbtGreen);
                avgb1 = (image[i][k].rgbtBlue + image[i][k - 1].rgbtBlue);
                //Sum of current and previous pixel's RGB values of next line
                avgr2 = (image[i + 1][k].rgbtRed + image[i + 1][k - 1].rgbtRed);
                avgg2 = (image[i + 1][k].rgbtGreen + image[i + 1][k - 1].rgbtGreen);
                avgb2 = (image[i + 1][k].rgbtBlue + image[i + 1][k - 1].rgbtBlue);

                //Sum of current and previous pixel's RGB values of previous line
                avgr3 = (image[i - 1][k].rgbtRed + image[i - 1][k - 1].rgbtRed);
                avgg3 = (image[i - 1][k].rgbtGreen + image[i - 1][k - 1].rgbtGreen);
                avgb3 = (image[i - 1][k].rgbtBlue + image[i - 1][k - 1].rgbtBlue);

                //Take out average of all the color values
                avgr = round((avgr1 + avgr2 + avgr3) / 6.0);
                avgg = round((avgg1 + avgg2 + avgg3) / 6.0);
                avgb = round((avgb1 + avgb2 + avgb3) / 6.0);

                //Assigns the avg color values to the img in buffer
                copy[i][k].rgbtBlue = avgb;
                copy[i][k].rgbtGreen = avgg;
                copy[i][k].rgbtRed = avgr;
            }
        }
    }
    for (int j = 0; j < height; j++)
    {
        for (int l = 0; l < width; l++)
        {
            image[j][l].rgbtBlue = copy[j][l].rgbtBlue;
            image[j][l].rgbtGreen = copy[j][l].rgbtGreen;
            image[j][l].rgbtRed = copy[j][l].rgbtRed;
        }
    }
    return;
}