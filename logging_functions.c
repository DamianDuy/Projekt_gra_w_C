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