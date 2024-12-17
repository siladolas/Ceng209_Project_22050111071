
#include "game.h"  // Include this to declare process_command
#include "file_parser.h"
#include "player.h"
#include "room.h"
#include "creature.h"
#include "item.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ROOMS 100
#define MAX_CREATURES 50
#define MAX_ITEMS 50
#define MAX_NAME_LENGTH 50


int main() {
    Room *rooms[MAX_ROOMS];
    Creature *creatures[MAX_CREATURES];
    Item *items[MAX_ITEMS];

    int room_count = 0, creature_count = 0, item_count = 0;

    load_rooms("rooms.txt", rooms, &room_count);
    load_creatures("creatures.txt", creatures, &creature_count, rooms, room_count);
    load_items("items.txt", items, &item_count, rooms, room_count);

    char player_name[MAX_NAME_LENGTH];
    printf("Enter your hero's name: ");
    fgets(player_name, MAX_NAME_LENGTH, stdin);
    player_name[strcspn(player_name, "\n")] = '\0';

    if (strlen(player_name) == 0) {
        strcpy(player_name, "Hero");
        printf("No name entered. Default name 'Hero' will be used.\n");
    }

    Player *player = create_player(player_name);
    Room *current_room = rooms[0];

    char command[256];
    printf("\nWelcome to the Dungeon Adventure Game: %s!\n", player->name);
    printf("Type 'help' for a list of commands or 'exit' to quit.\n\n");



    while (1) {
        printf("> ");
        fgets(command, 256, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            printf("Exiting the game. Goodbye!\n");
            break;
        }

        process_command(command, player, &current_room, creatures, creature_count, items, item_count);
    }

    for (int i = 0; i < room_count; i++) free(rooms[i]);
    for (int i = 0; i < creature_count; i++) free(creatures[i]);
    for (int i = 0; i < item_count; i++) free(items[i]);
    free_player(player);

    return 0;
}
