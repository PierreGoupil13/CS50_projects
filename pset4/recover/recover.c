#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE \n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    BYTE buffer[512];
    int firstJ = 0;
    FILE *img = NULL;
    //Avec ou sans le & ca marche, probablement car comme mon buffer est un tableau c'est en soi un pointer
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {

        //If the beginning of a JPEG file is found.
        if ((buffer[0] == 0xff) & (buffer[1] == 0xd8) & (buffer[2] == 0xff) & ((buffer[3] & 0xf0) == 0xe0))
        {

            //For the very first JPEG we found.
            if (firstJ == 0)
            {
                //Define the first name 000.jpeg
                string fileName = malloc(sizeof(char) * 8);
                sprintf(fileName, "%03i.jpg", firstJ);

                //Open the file with the right number
                img = fopen(fileName, "w");

                if (img == NULL)
                {
                    fclose(img);
                    printf("Could not create image file.\n");
                    return 5;
                }

                //Write in the file
                fwrite(buffer, 1, BLOCK_SIZE, img);

                firstJ++;
                //Free the memory from the name
                free(fileName);
            }
            else
            {
                //Closing the previous JPEG file
                fclose(img);

                //Beginning a new JPEG file
                string fileName = malloc(sizeof(char) * 8);
                sprintf(fileName, "%03i.jpg", firstJ);
                img = fopen(fileName, "w");

                if (img == NULL)
                {
                    fclose(img);
                    printf("Could not create image file.\n");
                    return 5;
                }

                //Write in the file
                fwrite(buffer, 1, BLOCK_SIZE, img);
                firstJ++;
                //Free the memory from the name
                free(fileName);
            }
        }
        else if (img != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    //Close the last image
    fclose(img);
    //Close the card
    fclose(card);

    return 0;
}