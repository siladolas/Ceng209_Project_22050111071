#include "file_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void load_rooms(const char *filename, Room **rooms, int *room_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open rooms file");
        exit(EXIT_FAILURE);
    }

    int up_connections[100], down_connections[100], left_connections[100], right_connections[100];

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Room *room = malloc(sizeof(Room));
        if (!room) {
            perror("Failed to allocate memory for room");
            exit(EXIT_FAILURE);
        }

        int up, down, left, right, trap;
        sscanf(line, "%d,%255[^,],%d,%d,%d,%d,%d", &room->id, room->description, &up, &down, &left, &right, &trap);

        room->up = room->down = room->left = room->right = NULL;
        room->trap = trap;

        rooms[*room_count] = room;
        up_connections[*room_count] = up;
        down_connections[*room_count] = down;
        left_connections[*room_count] = left;
        right_connections[*room_count] = right;

        (*room_count)++;
    }
    fclose(file);

    for (int i = 0; i < *room_count; i++) {
        rooms[i]->up = (up_connections[i] > 0) ? rooms[up_connections[i] - 1] : NULL;
        rooms[i]->down = (down_connections[i] > 0) ? rooms[down_connections[i] - 1] : NULL;
        rooms[i]->left = (left_connections[i] > 0) ? rooms[left_connections[i] - 1] : NULL;
        rooms[i]->right = (right_connections[i] > 0) ? rooms[right_connections[i] - 1] : NULL;
    }
}


void load_creatures(const char *filename, Creature **creatures, int *creature_count, Room *rooms[], int room_count) {

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open creatures file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Creature *creature = malloc(sizeof(Creature));
        if (!creature) {
            perror("Failed to allocate memory for creature");
            exit(EXIT_FAILURE);
        }
        srand((unsigned int)time(NULL));
        int room_id;
        char drop_item_name[256];
        sscanf(line, "%d,%255[^,],%d,%d,%255[^\n]", &room_id, creature->name, &creature->health, &creature->attack, drop_item_name);


        creature->room = (room_id > 0 && room_id <= room_count) ? rooms[room_id - 1] : NULL;

        Item *drop = malloc(sizeof(Item));
        if (!drop) {
            perror("Failed to allocate memory for drop item");
            exit(EXIT_FAILURE);
        }
        strncpy(drop->name, drop_item_name, sizeof(drop->name) - 1);
        drop->name[sizeof(drop->name) - 1] = '\0';
        strncpy(drop->effect, "Dropped by creature", sizeof(drop->effect) - 1);
        drop->effect[sizeof(drop->effect) - 1] = '\0';
        drop->room = NULL; // The drop will only appear after the creature is defeated

        creature->drop = drop;
        creatures[(*creature_count)++] = creature;
    }

    fclose(file);
}


void load_items(const char *filename, Item **items, int *item_count, Room *rooms[], int room_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open items file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Item *item = malloc(sizeof(Item));
        if (!item) {
            perror("Failed to allocate memory for item");
            exit(EXIT_FAILURE);
        }

        int room_id;
        sscanf(line, "%d,%255[^,],%255[^\n]", &room_id, item->name, item->effect);
        item->room = (room_id > 0 && room_id <= room_count) ? rooms[room_id - 1] : NULL;

        items[(*item_count)++] = item;
    }
    fclose(file);
}

