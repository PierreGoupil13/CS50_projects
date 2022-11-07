#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string key);
string rotate(string message, int k);

int main(int argc, string argv[])
{
    //Check the number of arguments
    if (argc != 2)
    {
        printf("Usage (number of arg): ./caesar key \n");
        return 1;
    }

    //Check if the string is only digits
    bool correct = only_digits(argv[1]);

    if (correct)
    {
        int key = atoi(argv[1]);

        //Make sur that the key is not superior to 26
        key = key % 26;
        string plain = get_string("plaintext:  ");
        string cipher = rotate(plain, key);
        printf("ciphertext:  %s\n", cipher);

    }
    else
    {
        printf("Usage(digits issue): ./caesar key \n");
        return 1;
    }

}

//Iterate through the string for the key and check that everything is a digit
bool only_digits(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (isdigit(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}

//Encrypt the message by rotation
string rotate(string message, int k)
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
                //Rotate it according to the caesar function
                c = ((c + k) % 26) + 97;
                //Convert it back to a char
                message[i] = c;
            }
            else if (isupper(message[i]))
            {
                int c = message[i] - 65;
                c = ((c + k) % 26) + 65;
                message[i] = c;
            }
        }
    }
    return message;
}