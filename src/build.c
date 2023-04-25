#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    if (!system("gcc -o bin/main src/main.c -Wall -Wextra -Werror -std=c18"))
    {
        printf("Comipled Successfully!\n"); 
        return EXIT_SUCCESS;
    }
    else
        return EXIT_FAILURE;
}