#include <cs50.h>
#include <stdio.h>

int ask_num(void);

int main(void)
{

    int n = ask_num();
    // Print the columns
    for (int i = 1; i <= n; i++)
    {
        // Print autant d'espace que la différence (n - i)
        for (int k = n; k > i; k--)
        {
            printf(" ");
        }
        // Print autant de # que la valeur de la différence (i - j)
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

//Function that asks the user for a number between 1 and 8 include
int ask_num(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n <= 0 || n > 8);
    return n;
}