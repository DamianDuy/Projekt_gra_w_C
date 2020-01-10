#include "function_headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>
#include <string.h>
#include "function_headers.h"

#define ANSI_COLOR_GREEN "\x1b[32m" //for making green console text using ANSI escape codes
#define ANSI_COLOR_RESET "\x1b[0m" //reseting console colors to default

typedef struct
{
    int coor_x;
    int coor_y;

}Coordinates;

void show_menu_after_logging(int checker, char login_to_display[])
{
    if(checker == 0)
    {
        printf("Welcome %s!\n", login_to_display);
        printf("1. Play.\n");
        printf("2. Show time played.\n");
        printf("3. Log out.\n");
        printf("4. Exit.\n");
    }

    if(checker == 1)   
    {   
        printf("Welcome again %s!\n", login_to_display);
        printf("1. Play again.\n");
        printf("2. Show time played.\n");
        printf("3. Log out.\n");
        printf("4. Exit.\n");
    } 
}

void ending_game()
{
    system("clear");
    printf("Thank you for playing!\n");
    printf("Bye ");
    setlocale(LC_ALL,"en_US.UTF-8");
    printf("👋");
    printf("\n");
    exit(0);
}
