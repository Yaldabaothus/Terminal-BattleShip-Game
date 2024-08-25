#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>


#define FIELD_WIDTH 24
#define FIELD_HEIGH 12
#define GAME_WIDTH  10
#define GAME_HEIGHT 10
#define SHIP "▒▒"


typedef enum {
    CARRIER = 5,
    BATTLESHIP = 4,
    CRUISER = 3,
    SUBMARINE = 2,
    DESTROYER = 1,
} ShipType;
typedef enum {UP, DOWN, LEFT, RIGHT} Direction;
typedef enum {START, PREPARATION, GAME, STOP, END} GamePhase;
typedef struct {
    size_t x;
    size_t y;
} Cursor;


void print_field(WINDOW* window, char game_field[GAME_HEIGHT][GAME_WIDTH]);
void print_ship(Cursor cursor, Direction direction, ShipType ship_type);


int main(void) {
    setlocale(LC_ALL, "");
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();

    Cursor player_cursor = {.x = 5, .y = 3};
    Direction current_direction = DOWN;
    ShipType current_ship = CARRIER;
    WINDOW* our_field = newwin(FIELD_HEIGH, FIELD_WIDTH, 4, 2);
    WINDOW* enemy_field = newwin(FIELD_HEIGH, FIELD_WIDTH, 4, 26);
    char our_game_field[GAME_HEIGHT][GAME_WIDTH] = {0};
    char enemy_game_field[GAME_HEIGHT][GAME_WIDTH] = {0};

    while (true) {
        mvprintw(player_cursor.x, player_cursor.y, "VV");
        print_field(our_field, our_game_field);
        print_field(enemy_field, our_game_field);
        mvprintw(16, 70, "1)    Carriers: ▒▒▒▒▒▒▒▒▒▒. Left: %d", 1);
        mvprintw(17, 70, "2) Battleships:   ▒▒▒▒▒▒▒▒. Left: %d", 2);
        mvprintw(18, 70, "3)    Cruisers:     ▒▒▒▒▒▒. Left: %d", 3);
        mvprintw(19, 70, "4)  Submarines:       ▒▒▒▒. Left: %d", 4);
        mvprintw(20, 70, "5)  Destroyers:         ▒▒. Left: %d", 5);
        print_ship(player_cursor, current_direction, current_ship);
        int input = getch();
        switch (input) {
            case KEY_UP: case 'w': case 'W':
                --player_cursor.x;
                break;
            case KEY_DOWN: case 's': case 'S':
                ++player_cursor.x;
                break;
            case KEY_LEFT: case 'a': case 'A':
                player_cursor.y -= 2;
                break;
            case KEY_RIGHT: case 'd': case 'D':
                player_cursor.y += 2;
                break;
            case 'r': case 'R':
                current_direction = (current_direction + 1) % 4;
                break;
            case '1':
                current_ship = CARRIER;
                break;
            case '2':
                current_ship = BATTLESHIP;
                break;
            case '3':
                current_ship = CRUISER;
                break;
            case '4':
                current_ship = SUBMARINE;
                break;
            case '5':
                current_ship = DESTROYER;
                break;
        }
        clear();
        refresh();
    }

    getch();
    endwin();
    return 0;
}


void print_ship(Cursor cursor, Direction direction, ShipType ship_type) {
    switch (direction) {
        case UP:
            for (size_t i = 0; i < ship_type; ++i) {
                mvprintw(cursor.x - i, cursor.y, "%s", SHIP);
            }
            break;
        case DOWN:
            for (size_t i = 0; i < ship_type; ++i) {
                mvprintw(cursor.x + i, cursor.y, "%s", SHIP);
            }
            break;
        case LEFT:
            for (size_t i = 0; i < ship_type; ++i) {
                mvprintw(cursor.x, cursor.y - (i * 2), "%s", SHIP);
            }
            break;
        case RIGHT:
            for (size_t i = 0; i < ship_type; ++i) {
                mvprintw(cursor.x, cursor.y + (i * 2), "%s", SHIP);
            }
           break;
    }
}


void print_field(WINDOW* window, char game_field[GAME_HEIGHT][GAME_WIDTH]) {
    box(window, 0, 0);
    wrefresh(window);
}
