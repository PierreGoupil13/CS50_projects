#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
string lowering(string word);
void who_won(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");


    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    who_won(score1, score2);
}

//Compare the score of the two player and decide on the outcomep
void who_won(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

//Take a string and give back a score.
int compute_score(string word)
{
    // TODO: Compute and return score for string

    //Lower ervery char in the string
    lowering(word);
    int score = 0;

    //Iterate over all the char in the string
    for (int i = 0; i < strlen(word); i++)
    {
        //check if the char is a letter or a special char and then assign a score.
        if (word[i] < 97 || word[i] > 122)
        {
            score = score + 0;
        }
        else
        {
            int n = word[i];
            score = score +  POINTS[n - 97];
        }
    }
    return score;
}

//Take a string and lower every caracter of it.
string lowering(string word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        word[i] = tolower(word[i]);
    }
    return word;
}