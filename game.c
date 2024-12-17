#include "game.h"
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "file_parser.h"
#include "room.h"
#include "player.h"
#include "creature.h"
#include "item.h"
#include <dirent.h>
#include <sys/stat.h> // For mkdir
#include <unistd.h>
#include "stdlib.h"

void check_trap(Player *player, Room *current_room) {
    if (current_room->trap) {
        int damage = player->health / 10;
        player->health -= damage;
        printf("You stepped into a trap! You lost %d health. Current health: %d\n", damage, player->health);
        if (player->health <= 0) {
            printf("You have been defeated by the trap! Game Over.\n");
            exit(0);
        }
    }
}
void process_command(const char *command, Player *player, Room **current_room, Creature **creatures, int creature_count, Item **items, int item_count) {
    if (strcmp(command, "look") == 0) {
        describe_room(*current_room);
        check_trap(player, *current_room);
        printf("Items in this room:\n");
        for (int i = 0; i < item_count; i++) {
            if (items[i]->room == *current_room) {
                printf("- %s: %s\n", items[i]->name, items[i]->effect);
            }
        }
        printf("Creatures in this room:\n");
        for (int i = 0; i < creature_count; i++) {
            if (creatures[i]->room == *current_room) {
                printf("- %s (Health: %d, Attack: %d)\n", creatures[i]->name, creatures[i]->health, creatures[i]->attack);
            }
        }
    }
    else if(strcmp(command, "attack") == 0){
        for (int i = 0; i < creature_count; i++) {
            if (creatures[i]->room == *current_room && creatures[i]->health > 0) {
                attack_creature(player, creatures[i]);
                if (creatures[i]->health <= 0) {


                    if (creatures[i]->drop) {
                        if (add_to_inventory(player, creatures[i]->drop->name)) {
                            printf("You picked up %s dropped by the %s.\n", creatures[i]->drop->name, creatures[i]->name);
                            free_item(creatures[i]->drop);
                            creatures[i]->drop = NULL;
                        } else {
                            printf("Your inventory is full! You cannot pick up %s.\n", creatures[i]->drop->name);
                        }
                    }
                }
                return;
            }
        }
        printf("There is no creature here to attack.\n");
    }
    else if (strncmp(command, "move ", 5) == 0) {
        char *direction = (char *)(command + 5);
        Room *next_room = NULL;

        if (strcmp(direction, "up") == 0) {
            next_room = (*current_room)->up;
        } else if (strcmp(direction, "down") == 0) {
            next_room = (*current_room)->down;
        } else if (strcmp(direction, "left") == 0) {
            next_room = (*current_room)->left;
        } else if (strcmp(direction, "right") == 0) {
            next_room = (*current_room)->right;
        }
        if (next_room) {
            *current_room = next_room;
            printf("You moved %s.\n", direction);
        } else {
            printf("You can't move %s from here.\n", direction);
        }
    }
    else if (strcmp(command, "exit") == 0) {
        printf("Exiting the game. Goodbye!\n");
    }
    else if (strcmp(command, "help") == 0) {
        display_help();
    }
    else if (strncmp(command, "pickup ", 7) == 0) {
            char *item_name = (char *)(command + 7);

            for (int i = 0; i < item_count; i++) {
                if (items[i]->room == *current_room && strcmp(items[i]->name, item_name) == 0) {
                    // Add to inventory
                    if (add_to_inventory(player, items[i]->name)) {
                        printf("You picked up %s.\n", items[i]->name);
                        items[i]->room = NULL;
                    } else {
                        printf("Your inventory is full! Cannot pick up %s.\n", item_name);
                    }
                    return;
                }
            }
            printf("Item '%s' is not in this room.\n", item_name);
        }
    else if(strncmp(command, "drop ", 5) == 0) {
        char *item_name = (char *) (command + 5);
        if (remove_from_inventory(player, item_name)) {
            for (int i = 0; i < item_count; i++) {
                if (items[i]->room == NULL && strcmp(items[i]->name, item_name) == 0) {
                    items[i]->room = *current_room;
                    printf("You dropped %s in this room.\n", item_name);
                    return;
                }
            }
            printf("You dropped eternally\n, %s", item_name);
        } else {
            printf("You don't have '%s' in your inventory.\n", item_name);

        }
    }
    else if (strcmp(command, "inventory") == 0) {
            display_inventory(player);
    }
    else if (strncmp(command, "use ", 4) == 0) {
        char *item_name = (char *)(command + 4);
        use_item(player, item_name, items, item_count);
    }
    else if (strncmp(command, "save ", 5) == 0) {
        char *filepath = (char *)(command + 5);
        save_game(filepath, player, *current_room, creatures, creature_count, items, item_count);
    } else if (strncmp(command, "load ", 5) == 0) {
        char *filepath = (char *)(command + 5);
        load_game(filepath, player, current_room, creatures, creature_count, items, item_count);
    } else if (strcmp(command, "list") == 0) {
        list_saved_games("./");
    }
    else {
            printf("Unknown command: '%s'\n", command);
        }
    }

void save_game(const char *filepath, Player *player, Room *current_room, Creature **creatures, int creature_count, Item **items, int item_count) {
    const char *saves_directory = "./saves";
    if (access(saves_directory, F_OK) != 0) {
        if (mkdir(saves_directory, 0777) != 0) {
            perror("Failed to create saves directory");
            return;
        }
    }

    FILE *file = fopen(filepath, "w");
    if (!file) {
        perror("Failed to save the game");
        return;
    }

    fprintf(file, "PLAYER\n");
    fprintf(file, "%s,%d,%d\n", player->name, player->health, player->strength);

    fprintf(file, "INVENTORY\n");
    for (int i = 0; i < player->inventory_count; i++) {
        fprintf(file, "%s\n", player->inventory[i]);
    }

    fprintf(file, "CURRENT_ROOM\n");
    fprintf(file, "%d\n", current_room->id);

    fprintf(file, "CREATURES\n");
    for (int i = 0; i < creature_count; i++) {
        fprintf(file, "%d,%s,%d,%d,%s\n", creatures[i]->room ? creatures[i]->room->id : -1,
                creatures[i]->name, creatures[i]->health, creatures[i]->attack,
                creatures[i]->drop ? creatures[i]->drop->name : "NONE");
    }


    fprintf(file, "ITEMS\n");
    for (int i = 0; i < item_count; i++) {
        fprintf(file, "%d,%s,%s\n", items[i]->room ? items[i]->room->id : -1,
                items[i]->name, items[i]->effect);
    }

    fclose(file);
    printf("Game saved to %s\n", filepath);
}


void load_game(const char *filepath, Player *player, Room **current_room, Creature **creatures, int creature_count, Item **items, int item_count) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Failed to load the game");
        return;
    }

    char line[256];


    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    sscanf(line, "%[^,],%d,%d", player->name, &player->health, &player->strength);


    fgets(line, sizeof(line), file);
    player->inventory_count = 0;
    while (fgets(line, sizeof(line), file) && strcmp(line, "CURRENT_ROOM\n") != 0) {
        line[strcspn(line, "\n")] = 0;
        player->inventory[player->inventory_count++] = strdup(line);
    }

    fgets(line, sizeof(line), file);
    int room_id;
    sscanf(line, "%d", &room_id);
    *current_room = room_id > 0 ? current_room[room_id - 1] : NULL;


    fgets(line, sizeof(line), file);
    for (int i = 0; i < creature_count; i++) {
        fgets(line, sizeof(line), file);
        int room_id;
        char drop_name[256];
        sscanf(line, "%d,%255[^,],%d,%d,%255[^\n]", &room_id, creatures[i]->name, &creatures[i]->health, &creatures[i]->attack, drop_name);
        creatures[i]->room = room_id > 0 ? current_room[room_id - 1] : NULL;
        if (strcmp(drop_name, "NONE") != 0) {

            strncpy(creatures[i]->drop->name, drop_name, sizeof(creatures[i]->drop->name) - 1);
        } else {
            creatures[i]->drop = NULL;
        }
    }

    fgets(line, sizeof(line), file);
    for (int i = 0; i < item_count; i++) {
        fgets(line, sizeof(line), file);
        int room_id;
        sscanf(line, "%d,%255[^,],%255[^\n]", &room_id, items[i]->name, items[i]->effect);
        items[i]->room = room_id > 0 ? current_room[room_id - 1] : NULL;
    }

    fclose(file);
    printf("Game loaded from %s\n", filepath);
}

void list_saved_games(const char *directory) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("Failed to open saves directory");
        return;
    }

    printf("Saved Files:\n");
    while ((entry = readdir(dp))) {
        if (entry->d_name[0] != '.') {
            printf("- %s\n", entry->d_name);
        }
    }

    closedir(dp);
}

