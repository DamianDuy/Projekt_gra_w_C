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

char getch() //implementation of getch() function from conio.h or ncurses libraries
{
    system ("/bin/stty raw");  //stty sets options for terminal, here used to enable raw input
    char ret = getchar();
    system ("/bin/stty cooked"); //disables raw input
    return ret;
}

void clear_input()
{
    while ( getchar() != '\n' ); //Takes away redundant input
}