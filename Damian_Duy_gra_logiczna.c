#include <stdio.h>

void show_map();
void show_starting_menu();
void show_continuing_menu();
void user_input();

int main()
{
    show_starting_menu();
    return 0;
}

void show_starting_menu()
{
    printf("1. Play\n");
    printf("2. Choose map\n");
    printf("3. Exit\n");
}