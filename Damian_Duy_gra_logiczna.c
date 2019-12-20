#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show_starting_menu(); 
void show_map(int tab_size_horizontal, int tab_size_vertical, int tab_map [][tab_size_vertical]);
void user_input(int tab_size_horizontal, int tab_size_vertical, int tab_map [][tab_size_vertical], int num_of_stars);
int stars_in_map_counter(int tab_size_horizontal, int tab_size_vertical, int tab_map [][tab_size_vertical]);
char getch();

int main()
{
    srand(time(NULL));
    int tab_size_horizontal = 20;
    int tab_size_vertical = 20;
    int map_size = tab_size_horizontal*tab_size_vertical;
    int tab_map[20][20] = {
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2} };
    show_starting_menu();
    int num_of_stars = stars_in_map_counter(tab_size_horizontal, tab_size_vertical, tab_map);
    user_input(tab_size_horizontal, tab_size_horizontal, tab_map, num_of_stars);
    printf("%d\n", stars_in_map_counter(tab_size_horizontal,tab_size_vertical,tab_map));
    return 0;
}

void show_starting_menu()
{
    printf("1. Play.\n");
    printf("2. Show highscore.\n");
    printf("3. Exit.\n");
}

void show_map(int tab_size_horizontal, int tab_size_vertical, int tab_map [][tab_size_vertical])
{
    for(int i = 0; i < tab_size_horizontal; i++)
    {
        for(int j = 0; j < tab_size_vertical; j++)
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
                printf("=");
                break;

                case 3:
                printf("*");
                break;

                case 4:
                printf(" ");
                break;
            }
       }
       printf ("\n");
    }   
}

int stars_in_map_counter(int tab_size_horizontal, int tab_size_vertical, int tab_map [][tab_size_vertical])
{
    int count_stars = 0;
    for(int i = 0; i < tab_size_horizontal; i++)
        for(int j = 0; j < tab_size_vertical; j++)
        {
            if(tab_map[i][j] == 3) count_stars++;
        }
    return count_stars;    
}

void user_input(int tab_size_horizontal, int tab_size_vertical, int tab_map [][tab_size_vertical], int num_of_stars)
{
    int coor_x = 1;
    int coor_y = 1;
    int stars_left = num_of_stars;
    char c;
    do
    {    
        system("clear");
        printf("Use w,s,a,d to move, e to exit.\n");
        show_map(tab_size_horizontal,tab_size_vertical,tab_map);
        c = getch();
        tab_map[coor_x][coor_y] = 4;
        switch(c)
        {
            case 'a':
            {
                if(tab_map[coor_x][coor_y-1] == 4) coor_y--;
                else if(tab_map[coor_x][coor_y-1] == 3)
                {
                    stars_left--;
                    coor_y--;
                }
                break;
            }
            case 'd':
            {
                if(tab_map[coor_x][coor_y+1] == 4) coor_y++;
                else if(tab_map[coor_x][coor_y-1] == 3)
                {
                    stars_left--;
                    coor_y++;
                }
                break;
            }
            case 'w':
            {
                if(tab_map[coor_x-1][coor_y] == 4) coor_x--;
                else if(tab_map[coor_x-1][coor_y] == 3)
                {
                    stars_left--;
                    coor_x--;
                }
                break;
            }
            case 's':
            {
                if(tab_map[coor_x+1][coor_y] == 4) coor_x++;
                else if(tab_map[coor_x+1][coor_y] == 3)
                {
                    stars_left--;
                    coor_x++;
                }
                break;
            }
        }
        tab_map[coor_x][coor_y] = 0;
    }while(c != 'e' && stars_left > 0);    
}

char getch()
{
    system ("/bin/stty raw");  
    char ret = getchar();
    system ("/bin/stty cooked");
    return ret;
}