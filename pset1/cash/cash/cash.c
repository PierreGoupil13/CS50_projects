#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // Prompt user for a non negative integer wich represent the money owed.
    int x;
    do
    {
        x = get_int("How much do you own the customer : ");
    }
    while (x < 0);

    return x;
}

int calculate_quarters(int cents)
{
    // CHeck if the cents value is indeed above 25, because if not, there is no way to give back quarters.
    if (cents >= 25)
    {
        // Return the number of quarters to give back
        return (cents / 25);
    }
    else
    {
        return 0;
    }

}

int calculate_dimes(int cents)
{
    // CHeck if the cents value is indeed above 10, because if not, there is no way to give back dimes.
    if (cents >= 10)
    {
        // Return the number of dimes to give back
        return (cents / 10);
    }
    else
    {
        return 0;
    }
}

int calculate_nickels(int cents)
{
    // CHeck if the cents value is indeed above 5, because if not, there is no way to give back nickels.
    if (cents >= 5)
    {
        // Return the number of nickels to give back
        return (cents / 5);
    }
    else
    {
        return 0;
    }
}

int calculate_pennies(int cents)
{
    // CHeck if the cents value is indeed above 1, because if not, there is no way to give back pennies.
    if (cents >= 1)
    {
        // Return the number of pennies to give back
        return (cents / 1);
    }
    else
    {
        return 0;
    }
}
