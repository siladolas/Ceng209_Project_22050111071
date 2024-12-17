#include "item.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

Item *create_item(const char *name, const char *effect, Room *room) {
    Item *item = malloc(sizeof(Item));
    if (!item) {
        perror("Failed to allocate memory for item");
        exit(EXIT_FAILURE);
    }

    strncpy(item->name, name, sizeof(item->name) - 1);
    item->name[sizeof(item->name) - 1] = '\0';

    strncpy(item->effect, effect, sizeof(item->effect) - 1);
    item->effect[sizeof(item->effect) - 1] = '\0';

    item->room = room;

    return item;
}

void free_item(Item *item) {
    free(item);
}
