/*
    A simple database to store the real names of clubs in Pro League Soccer
    Written by Oussama Teyib
    May, 2022 in Noudhibou
*/    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

#define MAX 30

typedef struct {
    int id;
    int isKnown;
    char fakeName[MAX];
    char realName[MAX];
} Club;

int main(void)
{
    int choice;
    system("cls");
    printf("What do you want:\n");
    printf("	1. Add a league\n");
    printf("	2. Modify a league\n");
    printf("	3. List a league\n");
    printf("	4. Remove a league\n");
    printf("	5. List all leagues\n");
    printf("	0. Exit\n");

    printf("\nEnter your choice: ");
    do
    {
        scanf("%d", &choice);
        if (choice < 0 || choice > 5)
            printf("\nEnter a valid choice [0, 5]: ");
    } while (choice < 0 || choice > 5);
    
    char temp[MAX], name[MAX];
    if (choice && choice != 5)
    {
        printf("Enter the name of the league: ");
        fflush(stdin);
        fgets(temp, MAX, stdin);
        temp[strlen(temp) - 1] = '\0';
        snprintf(name, MAX, "../results/%s.bin", temp);
    }

    int firstTime = 1;
    while (1)
    {
        if (!firstTime)
        {
            system("cls");
            printf("What do you want again:\n");
            printf("	1. Modify the league\n");
            printf("	2. List the league\n");
            printf("	3. Remove the league\n");
            printf("	0. Exit\n");

            printf("\nEnter your choice: ");
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

        FILE *league;
        int nClubs, again, counter;
        Club club;
        switch(choice)
        {
            case 1: // adding
            {
                league = fopen(name, "wb");
                if (!league)
                    die("Cannot create the file!");
                
                printf("\nEnter the number of clubs: ");
                do
                {              
                    fflush(stdin);
                    scanf("%d", &nClubs);
                    if (!nClubs)
                    {
                        printf("\nNumber of clubs can't be null!");
                        printf("\nEnter a valid number: ");
                    }
                } while (!nClubs);
                fwrite(&nClubs, sizeof nClubs, 1, league);
                
                counter = 0;
                while (counter < nClubs)
                {
                    club.id = counter + 1;
                    printf("\nClub #%d:\n", club.id);
                    printf ("The real name is known? (1/0): ");
                    fflush(stdin);
                    scanf("%d", &club.isKnown);

					if (club.isKnown)
					{
                        printf("Enter the fake name: ");
                        fflush(stdin);
                        fgets(club.fakeName, MAX, stdin);
                        club.fakeName[strlen(club.fakeName) - 1] = '\0';
                        
                        printf("Enter the real name: ");
                        fflush(stdin);
                        fgets(club.realName, MAX, stdin);
                        club.realName[strlen(club.realName) - 1] = '\0';
					}
					else
					{
					    strncpy(club.fakeName, "Not Given", MAX);
					    strncpy(club.realName, "Unknown", MAX);
					}	
                    
                    fwrite(&club, sizeof club, 1, league);
                    counter++;					
                }   
                  
                fclose(league);
                break;
            }
            
            case 2: // modifying
            {
                league = fopen(name, "rb+");
                if (!league)
                    die("Cannot open the file!");
                
                // skeep nClubs
                fread(&nClubs, sizeof nClubs, 1, league); 
                
                int tempID, found = 0;
                printf ("Enter the id of the club: ");
                fflush(stdin);
                scanf("%d", &tempID);
               
                while (1 == fread(&club, sizeof club, 1, league))
                {
                    if (club.id == tempID)
                    {
                        found = 1;
                        printf("\nClub #%d\n", club.id);
                        printf("Fake Name: %s\n", club.fakeName);
                        printf("Real Name: %s\n", club.realName);
                        
                        int tempChoice;
                        printf("\nWhat do you wanna modify:\n");
                        printf("    1. Fake Name\n");
                        printf("    2. Real Name\n");
                        printf("    3. Both\n");
                        printf("    0. Nothing\n");
                        printf("Enter your choice: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%d", &tempChoice);
                            if (tempChoice < 0 || tempChoice > 3)
                                printf("\nEnter a valid choice: ");
                        } while (tempChoice < 0 || tempChoice > 3);
                        
                        switch(tempChoice)
                        {
                            case 1: // modify fake name
                                printf("\nEnter the fake name: ");                           
                                fflush(stdin);
                                fgets(club.fakeName, MAX, stdin);
                                club.fakeName[strlen(club.fakeName) - 1] = '\0';
                                break;
                            
                            case 2: // modify real name
                                printf("Enter the real name: ");
                                fflush(stdin);
                                fgets(club.realName, MAX, stdin);
                                club.realName[strlen(club.realName) - 1] = '\0';
                                club.isKnown = 1;
                                break;
                            
                            case 3: // modify both of them
                                printf("\nEnter the fake name: ");
                                fflush(stdin);
                                fgets(club.fakeName, MAX, stdin);
                                club.fakeName[strlen(club.fakeName) - 1] = '\0';
                                
                                 printf("Enter the real name: ");
                                fflush(stdin);
                                fgets(club.realName, MAX, stdin);
                                club.realName[strlen(club.realName) - 1] = '\0';
                                club.isKnown = 1;
                                break;
                             
                            case 0:
                                printf("\nBe sure the next time!");
                        }
                        
                        if (tempChoice) 
                        {
                            fseek(league, - (long) sizeof club, SEEK_CUR);
                            fwrite(&club, sizeof club, 1, league);
                            printf("\nDone!");
                        }
                    }
                }
                
                if (!found)
                    printf("The ID is incorrect!\n");
                    
                fclose(league);
                break;
            }

            case 3: // print a league
            {
                league = fopen(name, "rb");
                if (!league)
                    die("Cannot open the file!");
                
                int empty = 1, printUnknown;;
                if (1 == fread(&nClubs, sizeof nClubs, 1, league))
                {
                    empty = 0;
                    printf ("\nNumber of clubs is: %d\n", nClubs);                                
                    printf("Print unknown clubs? (1/0): ");
                    fflush(stdin);
                    scanf("%d", &printUnknown);
                }         
                
                while (1 == fread(&club, sizeof club, 1, league))
                {
                    if (!printUnknown && !club.isKnown)
                        continue;
                        
                    printf("\nClub #%d\n", club.id);
                    printf("Fake Name: %s\n", club.fakeName);
                    printf("Real Name: %s\n", club.realName);
                }
                
                if (empty)
                    die("This file is empty!");
                    
                fclose(league);
                break;
            }
            
            case 4: // removing
                if(!remove(name))
                {
                    printf("Removed!\n");    
                    again = 0;    
                }
                else
                    die("Cannot find the file!");
                break;

            case 5: // print all leagues
            
                again = 0;
                break;

            case 0: // exiting
                again = 0;
        }   
        if (choice && choice != 4 && choice != 5)
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