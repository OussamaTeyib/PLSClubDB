#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int choice;
    printf("What do you want:\n");
    printf("	1. Add a league\n");
    printf("	2. Modify a league\n");
    printf("	3. Remove a league\n");
    printf("	4. List a league\n");
    printf("	5. List all leagues\n");
    printf("	6. Exit\n");

    do
    {
        fflush(stdin);
        scanf("%d", &choice);
        if (choice < 0 || choice > 6)
            printf("\nEnter a valid choice [0, 6]: ");
    } while (choice < 0 || choice > 6);


    











    return EXIT_SUCCESS;
}