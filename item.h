#ifndef ITEM_H
#define ITEM_H

#include "room.h"

typedef struct {
    char name[256];
    char effect[256];
    Room *room;
} Item;


Item *create_item(const char *name, const char *effect, Room *room);
void free_item(Item *item);

#endif
