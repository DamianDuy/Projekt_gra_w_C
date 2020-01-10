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

int main()
{
    srand(time(NULL));
    //Declaration of variables
    int tab_size_vertical = 20;
    int tab_size_horizontal = 20;
    int map_size = tab_size_vertical*tab_size_horizontal;
    int tab_map[20][20];
    int steps = 0; //For how many steps it took to complete the level
    int * ptr_steps; //Creating pointer to the variable steps so it can be changed in the user_input function
    ptr_steps = &steps;
    char choice;
    int checker = 0; //For checking which version of menu to show
    double total_time;
    char login_to_display[30];
    double time_you_play = 0;
    int which_map = 0;
    int temp_which_map = 0; //Variable for temporary holding the which_map variable value
    int if_the_same_map = 0; //Variable for checking if player wants to restart the game
    int * ptr_if_the_same_map; //Creating the pointer to the variable if_the_same_map so it can be changed in the user_input function
    ptr_if_the_same_map = &if_the_same_map;
    //End of the declaration of variables

    //Logging in
    logging_screen:
    logging_in(login_to_display);

    //Looped menu
    do
    {
        which_map = rand() % 7 + 1; //Getting a number of map that will be generated
        if(*ptr_if_the_same_map != 0) 
        {
            which_map = temp_which_map; 
            *ptr_if_the_same_map = 0; //Setting the flag to 0 again because else user would be playing on the same map over and over again
        }    
        temp_which_map = which_map; //This value will hold the which map value and will be used if the player wants to play on the same map again
        show_menu_after_logging(checker, login_to_display);
        choice = getch();
        switch(choice)
        {
            case '1':
            {
                checker = 1; //Changes to one because different menu will be shown now
                if(which_map == 1) generate_map_first(tab_size_vertical, tab_size_horizontal, tab_map);
                else if(which_map == 2) generate_map_second(tab_size_vertical, tab_size_horizontal, tab_map);
                else if(which_map == 3) generate_map_third(tab_size_vertical, tab_size_horizontal, tab_map);
                else if(which_map == 4) generate_map_fourth(tab_size_vertical, tab_size_horizontal, tab_map);
                else if(which_map == 5) generate_map_fifth(tab_size_vertical, tab_size_horizontal, tab_map);
                else if(which_map == 6) generate_map_sixth(tab_size_vertical, tab_size_horizontal, tab_map);
                else if(which_map == 7) generate_map_seventh(tab_size_vertical, tab_size_horizontal, tab_map);
                int num_of_stars = stars_in_map_counter(tab_size_vertical, tab_size_horizontal, tab_map);
                system("clear");
                printf("There are %d stars on the map.\n", stars_in_map_counter(tab_size_vertical, tab_size_horizontal,tab_map));
                sleep(2);
                time_t start = time(NULL);
                user_input(tab_size_vertical, tab_size_horizontal, tab_map, num_of_stars, ptr_steps, ptr_if_the_same_map);
                time_t end = time(NULL);
                total_time = difftime(end,start);
                if(stars_in_map_counter(tab_size_vertical, tab_size_horizontal, tab_map) == 0)
                {
                    printf("You got the stars in %d steps.\n", *ptr_steps);
                    printf("With time %.2f sec\n", total_time);
                    sleep(1);
                }
                time_you_play += total_time;
                break;   
            }

            case '2':
            {
                system("clear");
                if(time_you_play < 60)
                printf("You've been playing for %.2f seconds.\n", time_you_play);
                else
                printf("You've been playing for %.2f minutes.\n", time_you_play/60);
                break;
            } 

            case '3':
            {
                checker = 0; //Restarting which menu to show after user logs off
                time_you_play = 0; //Restarting time user has been playing for after user logs off
                goto logging_screen; //using goto to go back to loggin_in function
                break;
            }   

            case '4':
            {
                ending_game();
            }    

            default:
            {
                system("clear");
                break;
            }    
        }
    }while(1); //Infinite loop. Program ends with exits when user choose "Exit"

    return 0;
}