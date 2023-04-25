#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

typedef struct {
    int isKnown;
    char fakeName[20];
    char realName[20];
} Club;

int main(void)
{
    int choice;
    printf("What do you want:\n");
    printf("	1. Add a league\n");
    printf("	2. Modify a league\n");
    printf("	3. List a league\n");
    printf("	4. Remove a league\n");
    printf("	5. List all leagues\n");
    printf("	0. Exit\n");

    do
    {
        scanf("%d", &choice);
        if (choice < 0 || choice > 5)
            printf("\nEnter a valid choice [0, 5]: ");
    } while (choice < 0 || choice > 5);

    int firstTime = 1;
    while (1)
    {
        if (!firstTime)
        {
            printf("What do you want agin:\n");
            printf("	1. Modify the league\n");
            printf("	2. List the league\n");
            printf("	3. Remove the league\n");
            printf("	0. Exit\n");

            do
            {
                fflush(stdin);
                scanf("%d", &choice);
                if (choice < 0 || choice > 3)
                    printf("\nEnter a valid choice [0, 3]: ");
            } while (choice < 0 || choice > 3);
            
            if (choice)
                choice++;
        } 
        firstTime = 0;  

        FILE *lg;
        int nClubs, again;
        Club club;
        switch(choice)
        {
            case 1: // adding
                (void) lg;
                (void) nClubs;
                (void) club;
                break;

            case 2: // modifying
                break;

            case 3: // printing
                break;

            case 4: // removing
                break;

            case 5: // printing all leagues
                break;

            case 0: // exiting
                again = 0;
        }   
        if (choice)
        {
            printf("\nAgain? (1/0): ");
            fflush(stdin);
            scanf("%d", &again);
        }

        if (!again)
        {
            printf("\nGood Bye!");
            return EXIT_SUCCESS;
        }
    }
}