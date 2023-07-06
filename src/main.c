#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

void die(wchar_t *msg)
{
    fwprintf(stderr, L"%ls\n", msg);
    exit(EXIT_FAILURE);
}

#define MAX 30
#define MAX_LEAGUE_NAME 50

typedef struct {
    int id;
    int isKnown;
    wchar_t fakeName[MAX];
    wchar_t realName[MAX];
} Club;

int main(void)
{
    int choice;
    system("chcp 1252");
    system("cls");
    wprintf(L"What do you want:\n");
    wprintf(L"	1. Add a league\n");
    wprintf(L"	2. Modify a league\n");
    wprintf(L"	3. List a league\n");
    wprintf(L"	4. Remove a league\n");
    wprintf(L"	5. List all leagues\n");
    wprintf(L"	0. Exit\n");

    wprintf(L"\nEnter your choice: ");
    do
    {
        scanf("%d", &choice);
        if (choice < 0 || choice > 5)
            wprintf(L"\nEnter a valid choice [0, 5]: ");
    } while (choice < 0 || choice > 5);
    
    wchar_t temp[MAX_LEAGUE_NAME], name[MAX_LEAGUE_NAME];
    if (choice && choice != 5)
    {
        wprintf(L"Enter the name of the league: ");
        fflush(stdin);
        fgetws(temp, MAX_LEAGUE_NAME, stdin);
        temp[wcslen(temp) - 1] = L'\0';
        snwprintf(name, MAX_LEAGUE_NAME, L"../leagues/%ls.bin", temp);
    }

    int firstTime = 1;
    while (1)
    {
        if (!firstTime)
        {
            system("cls");
            wprintf(L"What do you want again:\n");
            wprintf(L"	1. Modify the league\n");
            wprintf(L"	2. List the league\n");
            wprintf(L"	3. Remove the league\n");
            wprintf(L"	0. Exit\n");

            wprintf(L"\nEnter your choice: ");
            do
            {
                fflush(stdin);
                scanf("%d", &choice);
                if (choice < 0 || choice > 3)
                    wprintf(L"\nEnter a valid choice [0, 3]: ");
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
                league = _wfopen(name, L"wb");
                if (!league)
                    die(L"Cannot create the corresponding file!");
                
                wprintf(L"\nEnter the number of clubs: ");
                do
                {              
                    fflush(stdin);
                    scanf("%d", &nClubs);
                    if (!nClubs)
                    {
                        wprintf(L"\nNumber of clubs can't be null!\n");
                        wprintf(L"Enter a valid number: ");
                    }
                } while (!nClubs);
                fwrite(&nClubs, sizeof nClubs, 1, league);
                
                counter = 0;
                while (counter < nClubs)
                {
                    club.id = counter + 1;
                    wprintf(L"\nClub #%d:\n", club.id);
                    wprintf(L"The real name is known? (1/0): ");
                    fflush(stdin);
                    scanf("%d", &club.isKnown);

                    if (club.isKnown)
                    {
                        wprintf(L"Enter the real name: ");
                        fflush(stdin);
                        fgetws(club.realName, MAX, stdin);
                        club.realName[wcslen(club.realName) - 1] = L'\0';

                        wprintf(L"Enter the fake name: ");
                        fflush(stdin);
                        fgetws(club.fakeName, MAX, stdin);
                        club.fakeName[wcslen(club.fakeName) - 1] = L'\0';
                    }
                    else
                    {
                        wcsncpy(club.fakeName, L"Not Given", MAX);
                        wcsncpy(club.realName, L"Unknown", MAX);
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
                league = _wfopen(name, L"rb+");
                if (!league)
                    die(L"Cannot open the corresponding file!");
                
                if (1 != fread(&nClubs, sizeof nClubs, 1, league))
                    die(L"The corresponding file is empty!"); 
                
                int tempID, found = 0;
                wprintf(L"Enter the id of the club: ");
                fflush(stdin);
                scanf("%d", &tempID);
               
                fseek(league, (long) (tempID - 1) * sizeof club, SEEK_CUR);

                if (1 == fread(&club, sizeof club, 1, league) && club.id == tempID)
                {
                    found = 1;
                    wprintf(L"\nClub #%d\n", club.id);
                    wprintf(L"Real Name: %ls\n", club.realName);
                    wprintf(L"Fake Name: %ls\n", club.fakeName);
                        
                    int tempChoice;
                    wprintf(L"\nWhat do you want:\n");
                    wprintf(L"	1. Modify the fake Name\n");
                    wprintf(L"	2. Modify the real Name\n");
                    wprintf(L"	3. Modify them both\n");
                    wprintf(L"	4. Set as unknown\n");
                    wprintf(L"	0. Nothing\n");
                    wprintf(L"Enter your choice: ");
                    do
                    {
                        fflush(stdin);
                        scanf("%d", &tempChoice);
                        if (tempChoice < 0 || tempChoice > 4)
                            wprintf(L"\nEnter a valid choice: ");
                    } while (tempChoice < 0 || tempChoice > 4); 
                       
                    switch(tempChoice)
                    {
                        case 1: // modify the fake name
                            wprintf(L"\nEnter the fake name: ");                           
                            fflush(stdin);
                            fgetws(club.fakeName, MAX, stdin);
                            club.fakeName[wcslen(club.fakeName) - 1] = L'\0';
                            break;
                            
                        case 2: // modify the real name
                            wprintf(L"\nEnter the real name: ");
                            fflush(stdin);
                            fgetws(club.realName, MAX, stdin);
                            club.realName[wcslen(club.realName) - 1] = L'\0';
                            club.isKnown = 1;
                            break;
                            
                        case 3: // modify them both
                            wprintf(L"\nEnter the real name: ");
                            fflush(stdin);
                            fgetws(club.realName, MAX, stdin);
                            club.realName[wcslen(club.realName) - 1] = L'\0';

                            wprintf(L"Enter the fake name: ");
                            fflush(stdin);
                            fgetws(club.fakeName, MAX, stdin);
                            club.fakeName[wcslen(club.fakeName) - 1] = L'\0';
      
                            club.isKnown = 1;
                            break;
               
                        case 4: // set as an unknown club
                            wcsncpy(club.fakeName, L"Not Given", MAX);
                            wcsncpy(club.realName, L"Unknown", MAX);
                            club.isKnown = 0;
                            break;

                        case 0:
                            wprintf(L"\nBe sure the next time!");
                    }
                        
                    if (tempChoice) 
                    {
                        fseek(league, - (long) sizeof club, SEEK_CUR);
                        fwrite(&club, sizeof club, 1, league);
                        wprintf(L"\nDone!");
                    }
                }
                
                if (!found)
                    wprintf(L"The ID is incorrect!\n");         
                
                fclose(league);    
                repeat = 1;
                break;
            }

            case 3: // print a league
            {
                league = _wfopen(name, L"rb");
                if (!league)
                    die(L"Cannot open the corresponding file!");
                
                if (1 != fread(&nClubs, sizeof nClubs, 1, league))
                    die(L"The corresponding file is empty!");

                int printUnknown;
                wprintf(L"\nNumber of clubs is: %d\n", nClubs);
                wprintf(L"Print unknown clubs? (1/0): ");
                fflush(stdin);
                scanf("%d", &printUnknown);                                         
                
                while (1 == fread(&club, sizeof club, 1, league))
                {
                    if (!printUnknown && !club.isKnown)
                        continue;
                        
                    wprintf(L"\nClub #%d\n", club.id);
                    wprintf(L"Real Name: %ls\n", club.realName);
                    wprintf(L"Fake Name: %ls\n", club.fakeName);
                }
 
                fclose(league);
                repeat = 1;
                break;
            }
            
            case 4: // removing
            {
                int tempChoice;
                wprintf(L"\nDo you want to remove the league? (1/0): ");
                fflush(stdin);
                scanf("%d", &tempChoice);
                if (tempChoice)
                {
                    if(!_wremove(name))
                    {
                        wprintf(L"Removed!\n");
                        repeat = 0;    
                        again = 0;    
                    }
                    else
                        die(L"Cannot find the file!");
                }
                else
                {
                    wprintf(L"\nBe sure the next time!");
                    repeat = 1;
                }
                break;
            }

            case 5: // print all leagues
            {  
                WIN32_FIND_DATAW findData;
                HANDLE hFind = FindFirstFileW(L"../leagues/*.bin", &findData);   
                if (hFind == INVALID_HANDLE_VALUE)
                    die(L"Cannot find any corresponding file!");

                int printUnknown;
                wprintf(L"Print unknown clubs? (1/0): ");
                fflush(stdin);
                scanf("%d", &printUnknown);

                do
                {
                    if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    {
                        wchar_t name[MAX_LEAGUE_NAME];                     
                        snwprintf(name, MAX_LEAGUE_NAME, L"../leagues/%ls", findData.cFileName);
                        league = _wfopen(name, L"rb");
                        if (!league)
                        {
                            fwprintf(stderr, L"ERROR: Cannot open '%ls'!\n", findData.cFileName);
                            continue;
                        }
                
                        if (1 != fread(&nClubs, sizeof nClubs, 1, league))
                        {
                            fwprintf(stderr, L"ERROR: '%ls' is empty!\n", findData.cFileName);
                            continue;
                        }

                        wprintf(L"\nLeague: %ls (%d clubs)\n", wcstok(findData.cFileName, L"."), nClubs);                                
                
                        while (1 == fread(&club, sizeof club, 1, league))
                        {
                            if (!printUnknown && !club.isKnown)
                                continue;
                        
                            wprintf(L"\n	Club #%d\n", club.id);
                            wprintf(L"	Real Name: %ls\n", club.realName);
                            wprintf(L"	Fake Name: %ls\n", club.fakeName);
                        }
                        wprintf(L"\n");
                        fclose(league);
                    }
                } while(FindNextFileW(hFind, &findData));

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
            wprintf(L"\nAgain? (1/0): ");
            fflush(stdin);
            scanf("%d", &again);
        }

        if (!again)
        {
            wprintf(L"\nGood Bye!");
            return EXIT_SUCCESS;
        }
    }
}