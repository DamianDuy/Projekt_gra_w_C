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
    double * ptr_total_time;
    ptr_total_time = &total_time;
    char login_to_display[30];
    double time_you_play = 0;
    double * ptr_time_you_play;
    ptr_time_you_play  = &time_you_play;
    int which_map = 0;
    int * ptr_which_map;
    ptr_which_map = &which_map;
    int temp_which_map = 0; //Variable for temporary holding the which_map variable value
    int * ptr_temp_which_map;
    ptr_temp_which_map = &temp_which_map;
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
        getting_random_map_number(ptr_which_map, ptr_if_the_same_map, ptr_temp_which_map);
        show_menu_after_logging(checker, login_to_display);
        choice = getch();
        switch(choice)
        {
            case '1':
            {
                checker = 1; //Changes to one because different menu will be shown now
                generating_drawn_map(ptr_which_map, tab_size_vertical, tab_size_horizontal, tab_map);
                gameplay(ptr_total_time, ptr_steps, ptr_if_the_same_map, tab_size_vertical, tab_size_horizontal, tab_map);
                time_you_play += total_time;
                break;   
            }

            case '2':
            {
                show_time_played(ptr_time_you_play);
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