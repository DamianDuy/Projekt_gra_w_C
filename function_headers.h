#ifndef _FUNCTION_HEADERS_GUARD
#define _FUNCTION_HEADERS_GUARD

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
void generate_map_sixth(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that generates map
void generate_map_seventh(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that generates map
void show_map(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that prints map
void user_input(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal], int num_of_stars, int * ptr_steps, int * ptr_if_the_same_map); //Function for taking user input and moving the character
int stars_in_map_counter(int tab_size_vertical, int tab_size_horizontal, int tab_map [] [tab_size_horizontal]); //Function that counts elements to pick on the map
void bonus(); //Function used for receiving bonus
void surprise(); //Function that draws a surprise
char getch(); //Function for taking input from keyboard without waiting for an enter
void clear_input(); //Function that clears redundand input (for example after scanf)
void ending_game(); //Function shows message and ends the game
void getting_random_map_number(int * ptr_which_map, int *ptr_if_the_same_map, int * ptr_temp_which_map);

#endif