#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show_starting_menu();
void generate_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); 
void show_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]);
void user_input(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal], int num_of_stars);
int stars_in_map_counter(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]);
char getch();

int main()
{
    srand(time(NULL));
    int tab_size_vertical = 20;
    int tab_size_horizontal = 20;
    int map_size = tab_size_vertical*tab_size_horizontal;
    int tab_map[20][20];
    generate_map(tab_size_vertical, tab_size_horizontal, tab_map);
    show_starting_menu();
    int num_of_stars = stars_in_map_counter(tab_size_vertical, tab_size_horizontal, tab_map);
    user_input(tab_size_vertical, tab_size_horizontal, tab_map, num_of_stars);
    printf("%d\n", stars_in_map_counter(tab_size_vertical, tab_size_horizontal,tab_map));
    return 0;
}

void show_starting_menu()
{
    printf("1. Play.\n");
    printf("2. Show highscore.\n");
    printf("3. Exit.\n");
}

void show_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
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

void user_input(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal], int num_of_stars)
{
    int coor_x = 1;
    int coor_y = 1;
    int stars_left = num_of_stars;
    char c;
    do
    {    
        system("clear");
        printf("Use w,s,a,d to move, e to exit.\n");
        show_map(tab_size_vertical, tab_size_horizontal,tab_map);
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
                else if(tab_map[coor_x][coor_y+1] == 3)
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
        system("clear");
        printf("Use w,s,a,d to move, e to exit.\n");
        show_map(tab_size_vertical, tab_size_horizontal,tab_map);    
}

char getch()
{
    system ("/bin/stty raw");  
    char ret = getchar();
    system ("/bin/stty cooked");
    return ret;
}

void generate_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
{
    //Filling an array with 4 where 4 represents ' '
    for(int i = 0; i < tab_size_vertical; i++)
        for(int j = 0; j < tab_size_horizontal; j++)
        tab_map[i][j] = 4;

    tab_map[1][1] = 0;    
    
    //Loops for drawing the edges of the map
    for(int i = 0; i < tab_size_vertical; i++) tab_map[i][0] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[0][j] = 2;
    for(int i = 1; i < tab_size_vertical; i++) tab_map[i][tab_size_horizontal - 1] = 1;
    for(int j = 0; j < tab_size_horizontal; j++)tab_map[tab_size_vertical - 1][j] = 2;

    tab_map[13][14] = 3;

    
    /*tab_map[20][20] = {
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
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2} };*/
}