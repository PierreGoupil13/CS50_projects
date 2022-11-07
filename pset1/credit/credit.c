#include <cs50.h>
#include <stdio.h>

int det_lenght(long creditNumber);
bool check_sum(long creditNumber);
void cardBan(long creditNumber, int lenght);

int main(void)
{
    long creditNumber = get_long("What's your credit card number : ");
    int lenght = det_lenght(creditNumber);
    //printf("%i \n",lenght);

    bool valid = check_sum(creditNumber);
    if (valid)
    {
        cardBan(creditNumber, lenght);
    }
    else
    {
        printf("INVALID\n");
    }

}

//Determine the lenght of the credit card number
int det_lenght(long creditNumber)
{
    if (creditNumber >= 1e15)
    {
        return 16;
    }
    else if (creditNumber >= 1e14)
    {
        return 15;
    }
    else if (creditNumber >= 1e12)
    {
        return 13;
    }
    else
    {
        return 0;
    }
}

bool check_sum(long creditNumber)
{
    int checkSum = 0;
    long temp = creditNumber;
    for (int pos = 0; temp > 0; pos ++)
    {
        //Check si on est sur une position pair
        if (pos % 2 == 0)
        {
            //Recupère le dernier digit
            checkSum = checkSum + (temp % 10);
            //On enlève le dernier digit.
            temp = temp / 10;
        }
        else
        {
            //Récupere le dernier digit
            int n1, n2;
            int tempNum = (temp % 10) * 2;
            if (tempNum > 9)
            {
                n1 = tempNum % 10;
                n2 = tempNum / 10;
                checkSum = checkSum + n1 + n2;
            }
            else
            {
                checkSum += tempNum;
            }
            //On enelève le dernier digit
            temp = temp / 10;
        }
    }
    return (checkSum % 10 == 0);
}

//Check what is the bank associated to the card
void cardBan(long creditNumber, int lenght)
{
    int temp;
    //Check if the lenght is correct and then if the first number are legit
    if (lenght == 16)
    {
        temp = creditNumber / 1e14;
        if (temp >= 51 && temp <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if (temp <= 49 && temp >= 40)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (lenght == 15)
    {
        temp = creditNumber / 1e13;
        if (temp == 34 || temp == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else if (lenght == 13)
    {
        temp = creditNumber / 1e12;
        if (temp == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}