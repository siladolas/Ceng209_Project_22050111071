#include "room.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Room *create_room(const char *description, int trap) {
    Room *room = (Room *)malloc(sizeof(Room));
    if (!room) {
        perror("Failed to allocate memory for room");
        exit(EXIT_FAILURE);
    }
    strncpy(room->description, description, sizeof(room->description) - 1);
    room->description[sizeof(room->description) - 1] = '\0'; // Ensure null-termination

    room->up = room->down = room->left = room->right = NULL;
    room->trap = trap;
    return room;
}

void connect_rooms(Room *from, Room *to, const char *direction) {
    if (strcmp(direction, "up") == 0) {
        from->up = to;
    } else if (strcmp(direction, "down") == 0) {
        from->down = to;
    } else if (strcmp(direction, "left") == 0) {
        from->left = to;
    } else if (strcmp(direction, "right") == 0) {
        from->right = to;
    }
}

void describe_room(Room *room) {
    printf("Room Description: %s\n", room->description);
    if (room->trap) {
        printf("Warning: This room contains a trap!\n");
    }
}

void free_room(Room *room) {
    free(room);
}


