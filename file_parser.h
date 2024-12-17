#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include "room.h"
#include "creature.h"
#include "item.h"

void load_rooms(const char *filename, Room **rooms, int *room_count);
void load_creatures(const char *filename, Creature **creatures, int *creature_count, Room *rooms[], int room_count);
void load_items(const char *filename, Item **items, int *item_count, Room *rooms[], int room_count);

#endif
