#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for their name
    string name = get_string("What's you'r name ? ");

    // Print hello and then the user name
    printf("hello, %s\n", name);
}