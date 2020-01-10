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

void user_input(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal], int num_of_stars, int * ptr_steps, int * ptr_if_the_same_map)
{
    Coordinates coordinate;
    coordinate.coor_x = 1;
    coordinate.coor_y = 1;
    int stars_left = num_of_stars;
    char c;
    int if_have_weapon = 0;
    do
    {    
        system("clear");
        printf("Use w,s,a,d to move, r to restart (after restarting the next game is on the same map), e to exit.\n");
        show_map(tab_size_vertical, tab_size_horizontal,tab_map);
        c = getch();
        tab_map[coordinate.coor_x][coordinate.coor_y] = 4;
        switch(c)
        {
            case 68: //Left arrow
            case 'a':
            {
                if(tab_map[coordinate.coor_x][coordinate.coor_y-1] != 1 && tab_map[coordinate.coor_x][coordinate.coor_y-1] != 2 && tab_map[coordinate.coor_x][coordinate.coor_y-1] != 3 && tab_map[coordinate.coor_x][coordinate.coor_y-1] != 100 && tab_map[coordinate.coor_x][coordinate.coor_y-1] != 200 && tab_map[coordinate.coor_x][coordinate.coor_y-1] != 300) coordinate.coor_y--;
                else if(tab_map[coordinate.coor_x][coordinate.coor_y-1] == 3)
                {
                    stars_left--;
                    coordinate.coor_y--;
                }
                else if(tab_map[coordinate.coor_x][coordinate.coor_y-1] == 100)
                {
                    coordinate.coor_y--;
                    bonus();
                }
                else if(tab_map[coordinate.coor_x][coordinate.coor_y-1] == 200)
                {
                    if(if_have_weapon > 0)
                    {
                        coordinate.coor_y--;
                        if_have_weapon--;
                    }
                }
                else if(tab_map[coordinate.coor_x][coordinate.coor_y-1] == 300)
                {
                    coordinate.coor_y--;
                    if_have_weapon++;
                }
                break;
            }
            case 67: //Right arrow
            case 'd':
            {
                if(tab_map[coordinate.coor_x][coordinate.coor_y+1] != 1 && tab_map[coordinate.coor_x][coordinate.coor_y+1] != 2 && tab_map[coordinate.coor_x][coordinate.coor_y+1] != 3 && tab_map[coordinate.coor_x][coordinate.coor_y+1] != 100 && tab_map[coordinate.coor_x][coordinate.coor_y+1] != 200 && tab_map[coordinate.coor_x][coordinate.coor_y+1] != 300) coordinate.coor_y++;
                else if(tab_map[coordinate.coor_x][coordinate.coor_y+1] == 3)
                {
                    stars_left--;
                    coordinate.coor_y++;
                }
                else if(tab_map[coordinate.coor_x][coordinate.coor_y+1] == 100)
                {
                    coordinate.coor_y++;
                    bonus();
                }
                else if(tab_map[coordinate.coor_x][coordinate.coor_y+1] == 200)
                {
                    if(if_have_weapon > 0)
                    {
                        coordinate.coor_y++;
                        if_have_weapon--;
                    }
                }
                else if(tab_map[coordinate.coor_x][coordinate.coor_y+1] == 300)
                {
                    coordinate.coor_y++;
                    if_have_weapon++;
                }
                break;
            }
            case 65: //Up arrow
            case 'w':
            {
                if(tab_map[coordinate.coor_x-1][coordinate.coor_y] != 1 && tab_map[coordinate.coor_x-1][coordinate.coor_y] != 2 && tab_map[coordinate.coor_x-1][coordinate.coor_y] != 3 && tab_map[coordinate.coor_x-1][coordinate.coor_y] != 100 && tab_map[coordinate.coor_x-1][coordinate.coor_y] != 200 && tab_map[coordinate.coor_x-1][coordinate.coor_y] != 300) coordinate.coor_x--;
                else if(tab_map[coordinate.coor_x-1][coordinate.coor_y] == 3)
                {
                    stars_left--;
                    coordinate.coor_x--;
                }
                else if(tab_map[coordinate.coor_x-1][coordinate.coor_y] == 100)
                {
                    coordinate.coor_x--;
                    bonus();
                }
                else if(tab_map[coordinate.coor_x-1][coordinate.coor_y] == 200)
                {
                    if(if_have_weapon > 0)
                    {
                        coordinate.coor_x--;
                        if_have_weapon--;
                    }
                }
                else if(tab_map[coordinate.coor_x-1][coordinate.coor_y] == 300)
                {
                    coordinate.coor_x--;
                    if_have_weapon++;
                }
                break;
            }
            case 66: //Down arrow
            case 's':
            {
                if(tab_map[coordinate.coor_x+1][coordinate.coor_y] != 1 && tab_map[coordinate.coor_x+1][coordinate.coor_y] != 2 && tab_map[coordinate.coor_x+1][coordinate.coor_y] != 3 && tab_map[coordinate.coor_x+1][coordinate.coor_y] != 100 && tab_map[coordinate.coor_x+1][coordinate.coor_y] != 200 && tab_map[coordinate.coor_x+1][coordinate.coor_y] != 300) coordinate.coor_x++;
                else if(tab_map[coordinate.coor_x+1][coordinate.coor_y] == 3)
                {
                    stars_left--;
                    coordinate.coor_x++;
                }
                else if(tab_map[coordinate.coor_x+1][coordinate.coor_y] == 100)
                {
                    coordinate.coor_x++;
                    bonus();
                }
                else if(tab_map[coordinate.coor_x+1][coordinate.coor_y] == 200)
                {
                    if(if_have_weapon > 0)
                    {
                        coordinate.coor_x++;
                        if_have_weapon--;
                    }
                }
                else if(tab_map[coordinate.coor_x+1][coordinate.coor_y] == 300)
                {
                    coordinate.coor_x++;
                    if_have_weapon++;
                }
                break;
            }
        }
        tab_map[coordinate.coor_x][coordinate.coor_y] = 0;
        (*ptr_steps)++;
    }while(c != 'e' && c != 'r' && stars_left > 0);
        system("clear");
        printf("Use w,s,a,d to move, r to restart (after restarting the next game is on the same map), e to exit.\n");
        show_map(tab_size_vertical, tab_size_horizontal,tab_map);
        if(c == 'r') *ptr_if_the_same_map = 1; //If user wants to play on the same map next time the value of if_the_same map changes to 1 and is used in the main function as a flag    
}

void bonus()
{
    system("clear");
    int success = 0;
    char a = rand() % 25 + 97;
    char b = rand() % 25 + 97;
    char c = rand() % 25 + 97;
    char d = rand() % 25 + 97;
    printf("%c %c %c %c\n", a, b, c, d);
    char input_var;
    sleep(1);
    system("clear");
    input_var = getchar();
    if(input_var == a)
    {
        clear_input();
        input_var = getchar();
        if(input_var == b)
        {
            clear_input();
            input_var = getchar();
            if(input_var == c)
            {
                clear_input();
                input_var = getchar();
                if(input_var == d)
                {
                    success = 1;
                    printf("Congratulations!\n");
                    printf("You got a bonus and unlocked a surprise.\n");
                    surprise();
                }
            
            }
        }
    }
    if(success == 0) printf("Sorry! You failed to get a bonus.\n");
    clear_input();
    sleep(2);
}

void surprise()
{
    //Goes to the bottom of the console
    for (int i = 0; i < 30; i++)
    {
        printf("\n");
    }
    system("clear");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("            /\\\n");
    printf("           /  \\\n");
    printf("          /____\\\n");
    printf("          |    |\n");
    printf("          |    |\n");
    printf("          |@@@@|\n");
    printf("          |    |\n");
    printf("          |    |\n");
    printf("          |____|\n");
    printf("             *\n");
    printf("              *\n");
    printf("              <*>\n");
    for (int j = 0; j < 15; j++)
    {
        //Delaying the movement
        for(unsigned i = 0; i < 100000000; i++)
        {

        }
        //Moves the drawing upward since the cursor is at the end of the console
        printf("\n");
    }
    for(unsigned i = 0; i < 100; i++)
        {
            printf("          \\   /\n");
            printf("           \\ /\n");
            printf("            *\n");
            printf("           / \\\n");
            printf("          /   \\\n");
            system("clear");
        }        
}