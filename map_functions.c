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

void show_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Array is filled with numbers, this function uses printf to print symbols 
    for(int i = 0; i < tab_size_vertical; i++)
    {
        for(int j = 0; j < tab_size_horizontal; j++)
        {
            switch (tab_map[i][j])
            {
                case 0:
                printf("&");
                break;

                case 1:
                printf("|");
                break;

                case 2:
                printf("-");
                break;

                case 3:
                printf("*");
                break;

                case 4:
                printf(" ");
                break;

                case 100:
                printf("$");
                break;

                case 200:
                printf("X");
                break;

                case 300:
                printf("!");
                break;

                default: //Have to be set to proper generate stars randomly later
                printf(" ");
                break;
            }
       }
       printf ("\n");
    }   
}

int stars_in_map_counter(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    int count_stars = 0;
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        {
            if(tab_map[i][j] == 3) count_stars++;
        }
    return count_stars;    
}

void getting_random_map_number(int * ptr_which_map, int * ptr_if_the_same_map, int * ptr_temp_which_map)
{
        *ptr_which_map = rand() % 7 + 1; //Getting a number of map that will be generated
        if(*ptr_if_the_same_map != 0) 
        {
            *ptr_which_map = *ptr_temp_which_map; 
            *ptr_if_the_same_map = 0; //Setting the flag to 0 again because else user would be playing on the same map over and over again
        }    
        *ptr_temp_which_map = *ptr_which_map; //This value will hold the which map value and will be used if the player wants to play on the same map again
}

//Here starts functions that manually generate maps
void generate_map_first(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Filling an array with 4 where 4 represents ' '
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        tab_map[i][j] = 4;

    //Setting the player
    tab_map[1][1] = 0;    
    
    //Loops for drawing the edges of the map
    for(int i = 0; i < tab_size_vertical; i++) tab_map[i][0] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[0][j] = 2;
    for(int i = 1; i < tab_size_vertical; i++) tab_map[i][tab_size_horizontal - 1] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[tab_size_vertical - 1][j] = 2;

    //Loops for drawing more interesting map
    for(int i = 2; i < 13; i++)
    {
        tab_map[i][2] = 1;
    }
    tab_map[10][2] = 4;
    for(int j = 3; j < 18; j++)
    {
        tab_map[2][j] = 2;
    }
    for(int i = 3; i < 14; i++)
    {
        tab_map[i][10] = 1;
    }
    tab_map[12][3] = 2;
    tab_map[12][4] = 2;
    tab_map[12][5] = 2;
    tab_map[11][5] = 1;
    tab_map[10][5] = 1;
    tab_map[9][5] = 1;
    tab_map[8][5] = 1;

    for(int j = 1; j < 19; j++)
    {
        tab_map[15][j] = 2;
    }
    
    tab_map[15][10] = 200; //Setting "X" on map

    //Generating stars randomly
    for(int i = 2; i < tab_size_vertical - 1; i++)
    {
        for(int j = 2; j < tab_size_horizontal - 1; j++)
        {
            if(tab_map[i][j] == 4)
            {
                tab_map[i][j] = rand() % 20 + 3;
            }
        }
    }
        
     tab_map[3][3] = 300;   //Setting "!" on map
     tab_map[17][17] = 100; //Setting "$" on map              
}

void generate_map_second(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Filling an array with 4 where 4 represents ' '
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        tab_map[i][j] = 4;

    //Setting the player
    tab_map[1][1] = 0;    
    
    //Loops for drawing the edges of the map
    for(int i = 0; i < tab_size_vertical; i++) tab_map[i][0] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[0][j] = 2;
    for(int i = 1; i < tab_size_vertical; i++) tab_map[i][tab_size_horizontal - 1] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[tab_size_vertical - 1][j] = 2;

    //Generating stars randomly
    for(int i = 2; i < tab_size_vertical - 1; i++)
    {
        for(int j = 2; j < tab_size_horizontal - 1; j++)
        {
            if(tab_map[i][j] == 4)
            {
                tab_map[i][j] = rand() % 20 + 3;
            }
        }
    }

    for(int j = 2; j < 18; j++)
    {
        tab_map[2][j] = 2;
    }

    tab_map[2][1] = 200;
    tab_map[3][17] = 1;
    tab_map[4][17] = 1;
    tab_map[5][16] = 2;
    tab_map[5][15] = 2;
    tab_map[5][14] = 2;
    tab_map[6][14] = 1;
    tab_map[7][14] = 200;
    tab_map[8][15] = 300;
    tab_map[8][14] = 1;
    tab_map[9][14] = 1;
    for(int j = 15; j < 19; j++)
    {
        tab_map[9][j] = 2;
    }
    tab_map[3][2] = 1;
    tab_map[4][2] = 1;
    tab_map[5][3] = 2;
    tab_map[5][4] = 2;
    tab_map[5][5] = 2;
    tab_map[6][5] = 1;
    tab_map[7][5] = 200;
    tab_map[8][5] = 1;
    tab_map[9][5] = 1;
    for(int j = 1; j < 5; j++)
    {
        tab_map[9][j] = 2;
    }
    tab_map[8][4] = 300;
    tab_map[8][3] = 3;
    tab_map[10][10] = 100;
}

void generate_map_third(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Filling an array with 4 where 4 represents ' '
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        tab_map[i][j] = 4;

    //Setting the player
    tab_map[1][1] = 0;    
    
    //Loops for drawing the edges of the map
    for(int i = 0; i < tab_size_vertical; i++) tab_map[i][0] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[0][j] = 2;
    for(int i = 1; i < tab_size_vertical; i++) tab_map[i][tab_size_horizontal - 1] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[tab_size_vertical - 1][j] = 2;

    //Generating stars randomly
    for(int i = 2; i < tab_size_vertical - 1; i++)
    {
        for(int j = 2; j < tab_size_horizontal - 1; j++)
        {
            if(tab_map[i][j] == 4)
            {
                tab_map[i][j] = rand() % 20 + 3;
            }
        }
    }

    for(int i = 1; i < 19; i++)
    {
        tab_map[i][9] = 1;
    }
    for(int j = 1; j < 19; j++)
    {
        tab_map[9][j] = 2;
    }
    tab_map[5][9] = 200;
    tab_map[14][9] = 200;
    tab_map[9][5] = 200;
    tab_map[9][14] = 200;
    tab_map[5][5] = 300;
    tab_map[6][6] = 300;
    tab_map[10][18] = 300;
}

void generate_map_fourth(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Filling an array with 4 where 4 represents ' '
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        tab_map[i][j] = 4;

    //Setting the player
    tab_map[1][1] = 0;    
    
    //Loops for drawing the edges of the map
    for(int i = 0; i < tab_size_vertical; i++) tab_map[i][0] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[0][j] = 2;
    for(int i = 1; i < tab_size_vertical; i++) tab_map[i][tab_size_horizontal - 1] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[tab_size_vertical - 1][j] = 2;

    //Generating stars randomly
    for(int i = 2; i < tab_size_vertical - 1; i++)
    {
        for(int j = 2; j < tab_size_horizontal - 1; j++)
        {
            if(tab_map[i][j] == 4)
            {
                tab_map[i][j] = rand() % 20 + 3;
            }
        }
    }

    for(int j = 2; j < 18; j++)
    {
        tab_map[2][j] = 2;
    }

    for(int j = 3; j < 18; j++)
    {
        tab_map[17][j] = 2;
    }

    for(int i = 3; i < 18; i++)
    {
        tab_map[i][2] = 1;
    }

    for(int i = 3; i < 18; i++)
    {
        tab_map[i][17] = 1;
    }

    tab_map[17][10] = 200;
    tab_map[17][18] = 200;
    tab_map[10][18] = 200;
    tab_map[5][18] = 300;
    tab_map[10][10] = 300;
    tab_map [2][18] = 200;
    tab_map[3][14] = 300;
    tab_map[1][16] = 300;
    tab_map[5][18] = 3;
    tab_map[14][18] = 3;
}

void generate_map_fifth(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Filling an array with 4 where 4 represents ' '
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        tab_map[i][j] = 4;

    //Setting the player
    tab_map[1][1] = 0;    
    
    //Loops for drawing the edges of the map
    for(int i = 0; i < tab_size_vertical; i++) tab_map[i][0] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[0][j] = 2;
    for(int i = 1; i < tab_size_vertical; i++) tab_map[i][tab_size_horizontal - 1] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[tab_size_vertical - 1][j] = 2;

    //Generating stars randomly
    for(int i = 2; i < tab_size_vertical - 1; i++)
    {
        for(int j = 2; j < tab_size_horizontal - 1; j++)
        {
            if(tab_map[i][j] == 4)
            {
                tab_map[i][j] = rand() % 20 + 3;
            }
        }
    }

    ///Generating figures
    tab_map[3][5] = 200;
    tab_map[3][6] = 300;
    tab_map[3][7] = 3;
    tab_map[4][5] = 200;
    tab_map[5][6] = 200;
    tab_map[5][7] = 200;
    tab_map[3][8] = 200;
    tab_map[4][8] = 200;
    tab_map[2][6] = 200;
    tab_map[2][7] = 200;

    tab_map[14][5] = 200;
    tab_map[15][6] = 300;
    tab_map[16][5] = 200;
    tab_map[15][5] = 200;
    tab_map[16][6] = 200;
    tab_map[16][7] = 200;
    tab_map[15][7] = 200;
    tab_map[14][7] = 200;
    tab_map[14][6] = 200;

    tab_map[10][10] = 200;
    tab_map[9][9] = 200;
    tab_map[9][10] = 3;
    tab_map[11][11] = 200;
    tab_map[10][12] = 200;
    tab_map[9][13] = 200;
    tab_map[8][8] = 200;
    tab_map[8][14] = 200;
    tab_map[8][9] = 200;
    tab_map[8][10] = 200;
    tab_map[8][11] = 200;
    tab_map[8][12] = 200;
    tab_map[8][13] = 200;

    tab_map[18][18] = 300;
}

void generate_map_sixth(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Filling an array with 4 where 4 represents ' '
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        tab_map[i][j] = 4;

    //Setting the player
    tab_map[1][1] = 0;    
    
    //Loops for drawing the edges of the map
    for(int i = 0; i < tab_size_vertical; i++) tab_map[i][0] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[0][j] = 2;
    for(int i = 1; i < tab_size_vertical; i++) tab_map[i][tab_size_horizontal - 1] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[tab_size_vertical - 1][j] = 2;

    //Generating stars randomly
    for(int i = 2; i < tab_size_vertical - 1; i++)
    {
        for(int j = 2; j < tab_size_horizontal - 1; j++)
        {
            if(tab_map[i][j] == 4)
            {
                tab_map[i][j] = rand() % 20 + 3;
            }
        }
    }

    tab_map[1][18] = 300;

    for(int j = 1; j < 19; j++)
    {
        tab_map[16][j] = 2;
    }

    tab_map[16][10] = 200;
    tab_map[17][1] = 300;
    tab_map[17][18] = 300;

    for(int j = 1; j < 10; j++)
    {
        tab_map[2][j] = 2;
    }

    for(int j = 11; j < 19; j++)
    {
        tab_map[2][j] = 2;
    }

    for(int i = 3; i < 16; i++)
    {
        tab_map[i][9] = 1;
    }

    for(int i = 3; i < 16; i++)
    {
        tab_map[i][11] = 1;
    }

    tab_map[10][9] = 200;
    tab_map[10][11] = 200;
}

void generate_map_seventh(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Filling an array with 4 where 4 represents ' '
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        tab_map[i][j] = 4;

    //Setting the player
    tab_map[1][1] = 0;    
    
    //Loops for drawing the edges of the map
    for(int i = 0; i < tab_size_vertical; i++) tab_map[i][0] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[0][j] = 2;
    for(int i = 1; i < tab_size_vertical; i++) tab_map[i][tab_size_horizontal - 1] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[tab_size_vertical - 1][j] = 2;

    //Generating stars randomly
    for(int i = 2; i < tab_size_vertical - 1; i++)
    {
        for(int j = 2; j < tab_size_horizontal - 1; j++)
        {
            if(tab_map[i][j] == 4)
            {
                tab_map[i][j] = rand() % 20 + 3;
            }
        }
    }

    tab_map[2][1] = 300;

    for(int i = 1; i < 3; i++)
    {
        tab_map[i][12] = 200;
    }

    tab_map[1][17] = 3;

    for(int j = 1; j < 19; j++)
    {
        tab_map[3][j] = 2;
    }

    tab_map[3][10] = 200;
    tab_map[4][1] = 300;

    for(int j = 1; j < 19; j++)
    {
        tab_map[7][j] = 2;
    }

    tab_map[7][10] = 200;
    tab_map[8][1] = 300;

    for(int j = 1; j < 19; j++)
    {
        tab_map[12][j] = 2;
    }

    tab_map[12][10] = 200;
    tab_map[14][1] = 300;

    for(int j = 1; j < 19; j++)
    {
        tab_map[17][j] = 2;
    }

    tab_map[17][10] = 200;
    tab_map[18][1] = 300;
    tab_map[18][17] = 3;
}
