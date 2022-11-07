#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int grade_score(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text to analyse: ");
        //printf("Text : %s\n", text);

    //Count and print the number of letters in the text
    int countLetters = count_letters(text);
    //printf("%i letters \n", countLetters);

    //Count and print the number of words in the text
    int countWords = count_words(text);
    //printf("%i words \n", countWords);

    //Count and print the number of sentences in the text
    int countSentences = count_sentences(text);
    //printf("%i sentences \n", countSentences);

    //Give the grade score
    int gradeScore = grade_score(countLetters, countWords, countSentences);

    //Adapt the text print to the grade score
    if(gradeScore <1)
    {
        printf("Before Grade 1\n");
    }
    else if(gradeScore >=16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", gradeScore);
    }


}

//Count the number if letter in the text
int count_letters(string text)
{
    int count = 0;
    //Iterate over all of the char of the text
    for (int i = 0; i < strlen(text); i++)
    {
        //Check if the char is a letter
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    //Return the number of letters in the text
    return count;
}

//Count the number of words in the text
int count_words(string text)
{
    int count = 1;
    //Iterate over all of the char of the text
    for (int i = 0; i < strlen(text); i++)
    {
        //Check if the char is a space, meaning that the word as ended and adds one to the count
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count;
}

//Count the number of sentences in the text
int count_sentences(string text)
{
    int count = 0;
    //Iterate over all of the char of the text
    for (int i = 0; i < strlen(text); i++)
    {
        //Check if the char is a . or ! or ? , meaning that the sentence as ended and adds one to the count
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

//Calculate the grade score of a text
int grade_score(int letters, int words, int sentences)
{
    //Count the average number of letters per 100 words
    float avgLetters = ((float)letters / words) * 100;
    //printf("%f\n", avgLetters);

    //Count the average number of sentences per 100 words
    float avgSentences = ((float)sentences / words) * 100.0;
    //printf("%f\n", avgSentences);

    //Give the grade score
    int gradeScore = round(0.0588 * avgLetters - 0.296 * avgSentences - 15.8);

    //printf("%i \n", gradeScore);

    return gradeScore;
}