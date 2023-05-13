#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void die(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

#define MAX 30
#define MAX_LEAGUE_NAME 50

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
    
    char temp[MAX_LEAGUE_NAME], name[MAX_LEAGUE_NAME];
    if (choice && choice != 5)
    {
        printf("Enter the name of the league: ");
        fflush(stdin);
        fgets(temp, MAX_LEAGUE_NAME, stdin);
        temp[strlen(temp) - 1] = '\0';
        snprintf(name, MAX_LEAGUE_NAME, "../leagues/%s.bin", temp);
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
        int nClubs, again, repeat, counter;
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
                        printf("\nNumber of clubs can't be null!\n");
                        printf("Enter a valid number: ");
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
                        printf("Enter the real name: ");
                        fflush(stdin);
                        fgets(club.realName, MAX, stdin);
                        club.realName[strlen(club.realName) - 1] = '\0';

                        printf("Enter the fake name: ");
                        fflush(stdin);
                        fgets(club.fakeName, MAX, stdin);
                        club.fakeName[strlen(club.fakeName) - 1] = '\0';
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
                repeat = 1;
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
                        printf("	1. Fake Name\n");
                        printf("	2. Real Name\n");
                        printf("	3. Both\n");
                        printf("	0. Nothing\n");
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
                            case 1: // modify the fake name
                                printf("\nEnter the fake name: ");                           
                                fflush(stdin);
                                fgets(club.fakeName, MAX, stdin);
                                club.fakeName[strlen(club.fakeName) - 1] = '\0';
                                break;
                            
                            case 2: // modify the real name
                                printf("\nEnter the real name: ");
                                fflush(stdin);
                                fgets(club.realName, MAX, stdin);
                                club.realName[strlen(club.realName) - 1] = '\0';
                                club.isKnown = 1;
                                break;
                            
                            case 3: // modify them both
                                printf("\nEnter the real name: ");
                                fflush(stdin);
                                fgets(club.realName, MAX, stdin);
                                club.realName[strlen(club.realName) - 1] = '\0';

                                printf("Enter the fake name: ");
                                fflush(stdin);
                                fgets(club.fakeName, MAX, stdin);
                                club.fakeName[strlen(club.fakeName) - 1] = '\0';
      
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
                            break;
                        }
                    }
                }
                
                if (!found)
                    printf("The ID is incorrect!\n");
                    
                fclose(league);
                repeat = 1;
                break;
            }

            case 3: // print a league
            {
                league = fopen(name, "rb");
                if (!league)
                    die("Cannot open the file!");
                
                if (1 != fread(&nClubs, sizeof nClubs, 1, league))
                    die("This file is empty!");

                int printUnknown;
                printf("\nNumber of clubs is: %d\n", nClubs);
                printf("Print unknown clubs? (1/0): ");
                fflush(stdin);
                scanf("%d", &printUnknown);                                         
                
                while (1 == fread(&club, sizeof club, 1, league))
                {
                    if (!printUnknown && !club.isKnown)
                        continue;
                        
                    printf("\nClub #%d\n", club.id);
                    printf("Fake Name: %s\n", club.fakeName);
                    printf("Real Name: %s\n", club.realName);
                }
 
                fclose(league);
                repeat = 1;
                break;
            }
            
            case 4: // removing
            {
                int tempChoice;
                printf("\nDo you want to remove the league? (1/0): ");
                fflush(stdin);
                scanf("%d", &tempChoice);
                if (tempChoice)
                {
                    if(!remove(name))
                    {
                        printf("Removed!\n");
                        repeat = 0;    
                        again = 0;    
                    }
                    else
                        die("Cannot find the file!");
                }
                else
                {
                    printf("\nBe sure the next time!");
                    repeat = 1;
                }
                break;
            }

            case 5: // print all leagues
            {  
                WIN32_FIND_DATAA findData;
                HANDLE hFind = FindFirstFileA("../leagues/*.bin", &findData);   
                if (hFind == INVALID_HANDLE_VALUE)
                    die("Cannot find any league!");

                int printUnknown;
                printf("Print unknown clubs? (1/0): ");
                fflush(stdin);
                scanf("%d", &printUnknown);

                do
                {
                    if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    {
                        char name[MAX_LEAGUE_NAME];                     
                        snprintf(name, MAX_LEAGUE_NAME, "../leagues/%s", findData.cFileName);
                        league = fopen(name, "rb");
                        if (!league)
                        {
                            fprintf(stderr, "ERROR: Cannot open '%s'!\n", findData.cFileName);
                            continue;
                        }
                
                        if (1 != fread(&nClubs, sizeof nClubs, 1, league))
                        {
                            fprintf(stderr, "ERROR: '%s' is empty!\n", findData.cFileName);
                            continue;
                        }

                        printf("\nLeague: %s (%d clubs)\n", strtok(findData.cFileName, "."), nClubs);                                
                
                        while (1 == fread(&club, sizeof club, 1, league))
                        {
                            if (!printUnknown && !club.isKnown)
                                continue;
                        
                            printf("\n	Club #%d\n", club.id);
                            printf("	Fake Name: %s\n", club.fakeName);
                            printf("	Real Name: %s\n", club.realName);
                        }
                        printf("\n");
                        fclose(league);
                    }
                } while(FindNextFileA(hFind, &findData));

                FindClose(hFind);
                again = 0;
                repeat = 0;
                break;
            }

            case 0: // exiting
                again = 0;
                repeat = 0;
        }   
        if (repeat)
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