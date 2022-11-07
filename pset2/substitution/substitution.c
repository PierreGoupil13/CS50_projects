#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_letters(string key);
string substitute(string message, string key);

int main(int argc, string argv[])
{


    //Check the number of arguments
    if (argc != 2)
    {
        printf("Usage (number of arg): ./caesar key \n");
        return 1;
    }

    //Check if the string is only digits
    bool correct = only_letters(argv[1]);

    //If the key is correct, put it in a string
    if(correct)
    {
        string key = argv[1];
        string plain = get_string("plaintext:  ");
        string cipher = substitute(plain, key);
        printf("ciphertext:  %s\n", cipher);
    }
    else
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

}

bool only_letters(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}

//Encrypt the message by substitution
string substitute(string message, string key)
{
    //Iterate over the all string
    for (int i = 0; i < strlen(message); i++)
    {
        //Check if the char is a number
        if (isalpha(message[i]))
        {
            //Check if the char is a lower or upper case and then rotate it
            if (islower(message[i]))
            {
                //Convert the char into his ascii value
                int c = message[i] - 97;
                for (int j = 0; c == i; i++)
                {
                    if (c == i)
                    {
                        c = key[i];
                    }
                }
                message[i] = c;
            }
            else if (isupper(message[i]))
            {
                int c = message[i] - 65;
                for (int j = 0; i < strlen(key); i++)
                {
                    if (c == key[i])
                    {
                        c = key[i];
                    }
                }
                message[i] = c;
            }
        }
    }
    return message;
}