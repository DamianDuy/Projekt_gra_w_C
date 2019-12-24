#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>
#include <string.h>

void logging_in(char login_to_display[]);
int reading_logins_from_file(char login [], char password []); //Function checks if user's login is in file and returns 0 if no, 1 if yes
void creating_an_account(); //Function adds a position to an array of structures
void show_menu_to_log_in(); //Function shows the menu with logging options
void show_menu_after_logging(int checker, char login_to_display []); //Function for showing menu
void generate_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that generates map
void show_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that prints map
void user_input(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal], int num_of_stars, int * ptr_steps); //Function for taking user input and moving the character
int stars_in_map_counter(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that counts elements to pick on the map
char getch(); //Function for taking input from keyboard without waiting for an enter
void move_enemy();

int main()
{
    //Declaration of variables
    srand(time(NULL));
    int tab_size_vertical = 20;
    int tab_size_horizontal = 20;
    int map_size = tab_size_vertical*tab_size_horizontal;
    int tab_map[20][20];
    int steps = 0;
    int * ptr_steps;
    ptr_steps = &steps;
    char choice;
    int checker = 0;
    double total_time;
    char login_to_display[30];
    double time_you_play = 0;
    //End of the declaration of variables

    //Logging in
    logging_screen:
    logging_in(login_to_display);

    //Looped menu
    do
    {
        show_menu_after_logging(checker, login_to_display);
        choice = getch();
        switch(choice)
        {
            case '1':
            {
                checker = 1;
                generate_map(tab_size_vertical, tab_size_horizontal, tab_map);
                int num_of_stars = stars_in_map_counter(tab_size_vertical, tab_size_horizontal, tab_map);
                printf("There are %d stars on the map\n", stars_in_map_counter(tab_size_vertical, tab_size_horizontal,tab_map));
                time_t start = time(NULL);
                user_input(tab_size_vertical, tab_size_horizontal, tab_map, num_of_stars, ptr_steps);
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
                checker = 0;
                time_you_play = 0;
                goto logging_screen;
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
    }while(1);

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

void user_input(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal], int num_of_stars, int * ptr_steps)
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
                if(tab_map[coor_x][coor_y-1] != 1 && tab_map[coor_x][coor_y-1] != 2 && tab_map[coor_x][coor_y-1] != 3 && tab_map[coor_x][coor_y-1] != 100) coor_y--;
                else if(tab_map[coor_x][coor_y-1] == 3)
                {
                    stars_left--;
                    coor_y--;
                }
                break;
            }
            case 'd':
            {
                if(tab_map[coor_x][coor_y+1] != 1 && tab_map[coor_x][coor_y+1] != 2 && tab_map[coor_x][coor_y+1] != 3 && tab_map[coor_x][coor_y+1] != 100) coor_y++;
                else if(tab_map[coor_x][coor_y+1] == 3)
                {
                    stars_left--;
                    coor_y++;
                }
                break;
            }
            case 'w':
            {
                if(tab_map[coor_x-1][coor_y] != 1 && tab_map[coor_x-1][coor_y] != 2 && tab_map[coor_x-1][coor_y] != 3 && tab_map[coor_x-1][coor_y] != 100) coor_x--;
                else if(tab_map[coor_x-1][coor_y] == 3)
                {
                    stars_left--;
                    coor_x--;
                }
                break;
            }
            case 's':
            {
                if(tab_map[coor_x+1][coor_y] != 1 && tab_map[coor_x+1][coor_y] != 2 && tab_map[coor_x+1][coor_y] != 3 && tab_map[coor_x+1][coor_y] != 100) coor_x++;
                else if(tab_map[coor_x+1][coor_y] == 3)
                {
                    stars_left--;
                    coor_x++;
                }
                break;
            }
        }
        tab_map[coor_x][coor_y] = 0;
        (*ptr_steps)++;
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

    //Generating stars randomly
    for(int i = 2; i < tab_size_vertical - 1; i++)
        for(int j = 2; j < tab_size_horizontal - 1; j++)
            tab_map[i][j] = rand() % 20 + 3;        

    
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
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,100,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2} };*/
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

        printf("Login: ");
        scanf("%29s", login);
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
            }
            else if(title_is_same == 0) 
            {
                break_imposter = 1;
            }
            title_is_same = 0;
            rewind(check_log);     
        }    
        fclose(check_log);
        printf("Password: ");
        scanf("%20s", password);
        
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
              printf("Insert password: ");
              scanf("%19s", password);
              //Functions reading_logins_from_file return 1 if success and 0 if failure
              if(reading_logins_from_file(login,password))
              {
                  printf("You've logged in succesfully!\n");
                  strcpy(login_to_display, login);
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