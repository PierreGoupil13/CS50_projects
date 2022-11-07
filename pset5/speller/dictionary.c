// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void free_list(node *list);

// TODO: Choose number of buckets in hash table
const unsigned int N = 416000;
int sizeDict = 0;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Hash the word from the text
    unsigned int hashCode = hash(word);

    //Set a cursor to navigate trought the list
    node *cursor = table[hashCode];

    //Loop trought the list
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }

        //Set the pointer to the next node
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char *lowWord = malloc(LENGTH);

    unsigned int code = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        lowWord[i] = tolower(word[i]);
        code += (lowWord[i]);
    }

    free(lowWord);

    return (code % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Open a dictionary and check that it doesn't return NULL
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not load dictionary");
        return false;
    }


    char newWord[LENGTH + 1];

    //Loop trought the dictionnary
    while (fscanf(dict, "%s", newWord) != EOF)
    {
        //Creating a new node and copying a word into it
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            printf("Can't create Node");
            return false;
        }

        //Copy the word to the node
        strcpy(newNode -> word, newWord);

        //Hashing the word
        unsigned int hashCode = hash(newWord);

        //Append the new node to the location given by the HashCode
        newNode -> next = table[hashCode];
        table[hashCode] = newNode;

        //Keep track of the dictionary size
        sizeDict++;

    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sizeDict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        free_list(table[i]);
    }
    return true;
}

void free_list(node *list)
{
    if (list == NULL)
    {
        return;
    }
    else
    {
        free_list(list -> next);
    }

    free(list);
}
