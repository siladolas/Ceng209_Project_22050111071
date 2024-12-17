

#ifndef GAME_H
#define GAME_H

#include "room.h"
#include "player.h"
#include "creature.h"
#include "item.h"
void check_trap(Player *player, Room *current_room);
void process_command(const char *command, Player *player, Room **current_room, Creature **creatures, int creature_count, Item **items, int item_count);
void list_saved_games(const char *directory);
void load_game(const char *filepath, Player *player, Room **current_room, Creature **creatures, int creature_count, Item **items, int item_count);
void save_game(const char *filepath, Player *player, Room *current_room, Creature **creatures, int creature_count, Item **items, int item_count);




#endif
