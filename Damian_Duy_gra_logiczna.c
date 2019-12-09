#include <stdio.h>

void show_starting_menu();
void show_continuing_menu();
void show_map(int tab_map [][10], int tab_size);
void user_input();
int stars_in_map_counter(int tab_map [][10], int tab_size);


int main()
{
    int tab_size = 10;
    int tab_map[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,2,1,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,3,1},
        {1,0,1,0,0,0,0,0,0,1},
        {1,0,1,1,3,1,1,0,0,1},
        {1,0,0,0,1,0,0,3,0,1},
        {1,3,0,0,1,0,0,0,0,1},
        {1,0,0,0,1,1,1,0,0,1},
        {1,0,3,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1} };
    show_starting_menu();
    show_map(tab_map, tab_size);
    printf("%d\n", stars_in_map_counter(tab_map, tab_size));
    return 0;
}

void show_starting_menu()
{
    printf("1. Play\n");
    printf("2. Choose map\n");
    printf("3. Exit\n");
}

void show_continuing_menu()
{
    printf("1. Play again\n");
    printf("2. Change map\n");
    printf("3. Exit\n");
}

void show_map(int tab_map [][10], int tab_size)
{
    for(int i = 0; i < tab_size; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            switch (tab_map[i][j])
            {
                case 0:
                printf(" ");
                break;

                case 1:
                printf("|");
                break;

                case 2:
                printf("&");
                break;

                case 3:
                printf("*");
                break;
            }
       }
       printf ("\n");
    }   
}

int stars_in_map_counter(int tab_map [][10], int tab_size)
{
    int count_stars = 0;
    for(int i = 0; i < tab_size; i++)
        for(int j = 0; j < tab_size; j++)
        {
            if(tab_map[i][j] == 3) count_stars++;
        }
    return count_stars;    
}