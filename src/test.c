#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(void)
{
    HANDLE hFind;
    WIN32_FIND_DATAA findData;

    hFind = FindFirstFileA("*.bin", &findData);

    /*if (hFind == INVALID_HANDLE_VALUE);
    {
        fprintf(stderr, "Ther is no files!\n");
        return EXIT_FAILURE;
    }*/

    do
    {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            printf("- '%s'\n", findData.cFileName);

    } while(FindNextFileA(hFind, &findData));

    FindClose(hFind);
    return EXIT_SUCCESS;
}