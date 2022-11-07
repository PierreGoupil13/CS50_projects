#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long test = 4003600000003514;
    printf("%ld \n", (test % 100) / 10);
}