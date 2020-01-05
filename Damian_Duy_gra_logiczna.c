#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>
#include <string.h>

#define ANSI_COLOR_GREEN "\x1b[32m" //for making green console text using ANSI escape codes
#define ANSI_COLOR_RESET "\x1b[0m" //reseting console colors to default

void logging_in(char login_to_display[]); //Function used for logging in
int reading_logins_from_file(char login [], char password []); //Function checks if user's login is in file and returns 0 if no, 1 if yes
void creating_an_account(); //Function adds a position to an array of structures
void show_menu_to_log_in(); //Function shows the menu with logging options
void show_menu_after_logging(int checker, char login_to_display []); //Function for showing menu
void generate_map_first(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that generates map
void generate_map_second(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that generates map
void generate_map_third(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that generates map
void generate_map_fourth(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that generates map
void generate_map_fifth(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that generates map
void show_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that prints map
void user_input(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal], int num_of_stars, int * ptr_steps, int * ptr_if_the_same_map); //Function for taking user input and moving the character
int stars_in_map_counter(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that counts elements to pick on the map
void bonus(); //Function used for receiving bonus
void surprise(); //Function that draws a surprise
char getch(); //Function for taking input from keyboard without waiting for an enter
void clear_input(); //Function that clears redundand input (for example after scanf)

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
        which_map = rand() % 5 + 1; //Getting a number of map that will be generated
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
                system("clear");
                printf("Thank you for playing!\n");
                printf("Bye ");
                setlocale(LC_ALL,"en_US.UTF-8");
                printf("👋");
                printf("\n");
                exit(0);
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

void user_input(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal], int num_of_stars, int * ptr_steps, int * ptr_if_the_same_map)
{
    int coor_x = 1;
    int coor_y = 1;
    int stars_left = num_of_stars;
    char c;
    int if_have_weapon = 0;
    do
    {    
        system("clear");
        printf("Use w,s,a,d to move, r to restart (after restarting the next game is on the same map), e to exit.\n");
        show_map(tab_size_vertical, tab_size_horizontal,tab_map);
        c = getch();
        tab_map[coor_x][coor_y] = 4;
        switch(c)
        {
            case 68: //Left arrow
            case 'a':
            {
                if(tab_map[coor_x][coor_y-1] != 1 && tab_map[coor_x][coor_y-1] != 2 && tab_map[coor_x][coor_y-1] != 3 && tab_map[coor_x][coor_y-1] != 100 && tab_map[coor_x][coor_y-1] != 200 && tab_map[coor_x][coor_y-1] != 300) coor_y--;
                else if(tab_map[coor_x][coor_y-1] == 3)
                {
                    stars_left--;
                    coor_y--;
                }
                else if(tab_map[coor_x][coor_y-1] == 100)
                {
                    coor_y--;
                    bonus();
                }
                else if(tab_map[coor_x][coor_y-1] == 200)
                {
                    if(if_have_weapon > 0)
                    {
                        coor_y--;
                        if_have_weapon--;
                    }
                }
                else if(tab_map[coor_x][coor_y-1] == 300)
                {
                    coor_y--;
                    if_have_weapon++;
                }
                break;
            }
            case 67: //Right arrow
            case 'd':
            {
                if(tab_map[coor_x][coor_y+1] != 1 && tab_map[coor_x][coor_y+1] != 2 && tab_map[coor_x][coor_y+1] != 3 && tab_map[coor_x][coor_y+1] != 100 && tab_map[coor_x][coor_y+1] != 200 && tab_map[coor_x][coor_y+1] != 300) coor_y++;
                else if(tab_map[coor_x][coor_y+1] == 3)
                {
                    stars_left--;
                    coor_y++;
                }
                else if(tab_map[coor_x][coor_y+1] == 100)
                {
                    coor_y++;
                    bonus();
                }
                else if(tab_map[coor_x][coor_y+1] == 200)
                {
                    if(if_have_weapon > 0)
                    {
                        coor_y++;
                        if_have_weapon--;
                    }
                }
                else if(tab_map[coor_x][coor_y+1] == 300)
                {
                    coor_y++;
                    if_have_weapon++;
                }
                break;
            }
            case 65: //Up arrow
            case 'w':
            {
                if(tab_map[coor_x-1][coor_y] != 1 && tab_map[coor_x-1][coor_y] != 2 && tab_map[coor_x-1][coor_y] != 3 && tab_map[coor_x-1][coor_y] != 100 && tab_map[coor_x-1][coor_y] != 200 && tab_map[coor_x-1][coor_y] != 300) coor_x--;
                else if(tab_map[coor_x-1][coor_y] == 3)
                {
                    stars_left--;
                    coor_x--;
                }
                else if(tab_map[coor_x-1][coor_y] == 100)
                {
                    coor_x--;
                    bonus();
                }
                else if(tab_map[coor_x-1][coor_y] == 200)
                {
                    if(if_have_weapon > 0)
                    {
                        coor_x--;
                        if_have_weapon--;
                    }
                }
                else if(tab_map[coor_x-1][coor_y] == 300)
                {
                    coor_x--;
                    if_have_weapon++;
                }
                break;
            }
            case 66: //Down arrow
            case 's':
            {
                if(tab_map[coor_x+1][coor_y] != 1 && tab_map[coor_x+1][coor_y] != 2 && tab_map[coor_x+1][coor_y] != 3 && tab_map[coor_x+1][coor_y] != 100 && tab_map[coor_x+1][coor_y] != 200 && tab_map[coor_x+1][coor_y] != 300) coor_x++;
                else if(tab_map[coor_x+1][coor_y] == 3)
                {
                    stars_left--;
                    coor_x++;
                }
                else if(tab_map[coor_x+1][coor_y] == 100)
                {
                    coor_x++;
                    bonus();
                }
                else if(tab_map[coor_x+1][coor_y] == 200)
                {
                    if(if_have_weapon > 0)
                    {
                        coor_x++;
                        if_have_weapon--;
                    }
                }
                else if(tab_map[coor_x+1][coor_y] == 300)
                {
                    coor_x++;
                    if_have_weapon++;
                }
                break;
            }
        }
        tab_map[coor_x][coor_y] = 0;
        (*ptr_steps)++;
    }while(c != 'e' && c != 'r' && stars_left > 0);
        system("clear");
        printf("Use w,s,a,d to move, r to restart (after restarting the next game is on the same map), e to exit.\n");
        show_map(tab_size_vertical, tab_size_horizontal,tab_map);
        if(c == 'r') *ptr_if_the_same_map = 1; //If user wants to play on the same map next time the value of if_the_same map changes to 1 and is used in the main function as a flag    
}


char getch() //implementation of getch() function from conio.h or ncurses libraries
{
    system ("/bin/stty raw");  //stty sets options for terminal, here used to enable raw input
    char ret = getchar();
    system ("/bin/stty cooked"); //disables raw input
    return ret;
}

void generate_map_first(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal])
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

void creating_an_account()
{
        int title_is_same = 0;
        int break_imposter = 0;
        char temp_login [30];
        char temp_password [20];
        char login [30];
        char password [20];

        //Reading from the file
        FILE *check_log;
        check_log = fopen("logins.txt", "r");
        if(check_log == NULL)
        {
            printf("Encountered error.\n");
            printf("File logins.txt is missing.\n");
            printf("Make sure file logins.txt is present before playing the game.\n");
            exit(1);
        }
        printf(ANSI_COLOR_GREEN "Login can not include spaces. The spaces in input will be ignored." ANSI_COLOR_RESET "\n");
        printf("Login: ");
        scanf("%29s", login);
        clear_input(); //flushing the input buffer
        while(break_imposter == 0)
        {
            while(fscanf(check_log, "%29s %*s", temp_login) > 0 && title_is_same == 0)
            {
                if(strcmp(temp_login, login) == 0)
                {
                    title_is_same = 1;
                }
            }
            if(title_is_same == 1)
            {
                printf("This account already exists.\n");
                printf("Login: ");
                scanf("%29s", login);
                clear_input(); //flushing the input buffer
                
            }
            else if(title_is_same == 0) 
            {
                break_imposter = 1;
            }
            title_is_same = 0;
            rewind(check_log); //Going back to the beginning of the file     
        }    
        fclose(check_log);
        printf("Password: ");
        scanf("%20s", password);
        clear_input(); //flushing the input buffer
        
        //Writing to file
        FILE *login_file;
        login_file = fopen("logins.txt", "a");
        fprintf(login_file,"%s ", login);
        fprintf(login_file,"%s\n", password);
        fclose(login_file);
}

void logging_in(char login_to_display [])
{
    char login [30];
    char password [20];
    char choice;
    do
    {
        show_menu_to_log_in();
        choice = getch();

        switch(choice)
        {
            case '1':
          {
            system("clear");
            creating_an_account();
            break;
          }
          
          case '2':
          {
              system("clear");
              printf("Insert login: ");
              scanf("%29s", login);
              clear_input(); //flushing the input buffer
              printf("Insert password: ");
              scanf("%19s", password);
              clear_input(); //flushing the input buffer
              //Functions reading_logins_from_file return 1 if success and 0 if failure
              if(reading_logins_from_file(login,password))
              {
                  printf("You've logged in succesfully!\n");
                  strcpy(login_to_display, login);
                  system("clear");
              }
              else
              {
                  printf("Wrong login or password.\n");
                  sleep(3);
                  logging_in(login_to_display);
              }
              break;
          }
          
          case '3':
          {
            system("clear");
            printf("You are exiting the game.\n");
            printf("Bye ");
            setlocale(LC_ALL,"en_US.UTF-8");
            printf("😢");
            printf("\n");
            exit(0);
          }    

          default:
          {
            system("clear");
            break;
          }  
        }
    }while(choice != '2');        
}

void show_menu_to_log_in()
{
    system("clear");
    printf("1. Create an account.\n");
    printf("2. Log in.\n");
    printf("3. Exit.\n");
}

int reading_logins_from_file(char login [], char password [])
{
        char from_file_login [30];
        char from_file_password [20];
        int log_and_pas_correct = 0;
        FILE *logins;
        logins = fopen("logins.txt", "r");
        if(logins == NULL)
        {
            printf("Encountered error.\n");
            printf("File logins.txt is missing.\n");
            printf("Make sure file logins.txt is present before playing the game.\n");
            exit(1);
        }
        while(fscanf(logins, "%29s %19s", from_file_login, from_file_password) > 0 && log_and_pas_correct == 0)
        {
            if(strcmp(from_file_login, login) == 0)
            {
                if(strcmp(from_file_password, password) == 0)
                {
                    log_and_pas_correct = 1;
                }
            }
        }
        if(log_and_pas_correct == 1)
        {
            fclose(logins);
            return 1;
        }
        else
        {
            fclose(logins);
            return 0;
        }    
            
}

void clear_input()
{
    while ( getchar() != '\n' ); //Takes away redundant input
}